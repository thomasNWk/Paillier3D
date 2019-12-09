#include "paillier.hpp"
#include "rsa.hpp"  // Used for utility functions
#include <iostream>

namespace encrypt3d {

    uint64_t mpz2ull(mpz_t z)
    {
        uint64_t result = 0;
        mpz_export(&result, 0, -1, sizeof result, 0, 0, z);
        return result;
    }

    void ull2mpz(mpz_t z, uint64_t ull)
    {
        mpz_import(z, 1, -1, sizeof ull, 0, 0, &ull);
    }

    Paillier::Paillier(int l) { 
        m_l = l;      

        // mpv : maximum possible value 
        m_mpv = pow(2,23*l) - 1;  // mantissa size (bits) * block size ()
        // public key n needs to be under the mpv but close to it
        std::cout << "MPV = " << m_mpv << "\n";

        m_pbk = pcs_init_public_key();
        m_pvk = pcs_init_private_key();
        m_hr = hcs_init_random();
        
        // Generate a key pair with modulus of correct size so that public key n is under the mpv but close to it
        pcs_generate_key_pair(m_pbk, m_pvk, m_hr, 21);    

        while( mpz_get_ui(m_pbk->n) > m_mpv) {
            //std::cout << "MPV = " << m_mpv << "\nn = "<< mpz_get_ui(m_pbk->n) << std::endl; 
            
            pcs_public_key *pk = pcs_init_public_key();
            pcs_private_key *m_pvk = pcs_init_private_key();
            hcs_random *m_hr = hcs_init_random();            
            // Generate a key pair with modulus of size 2048 bits
            pcs_generate_key_pair(m_pbk, m_pvk, m_hr, 21);    
        } 

        // Print keys infos
        std::cout << "n = " << mpz_get_ui(m_pbk->n) << "\n"; 
        std::cout << "n2 = " << mpz_get_ui(m_pbk->n2) << "\n";  
        std::cout << "g = " << mpz_get_ui(m_pbk->g) << "\n"; 
        std::cout << "mu = " << mpz_get_ui(m_pvk->mu) << "\n";   
        std::cout << "lambda = " << mpz_get_ui(m_pvk->lambda) << "\n";   
    }

    uint32_t Paillier::encrypt(uint32_t block, unsigned int msg) const
    {   
        std::cout << "Shrinking" << std::endl;
        // Shrinking
        uint32_t shrinkedBlock = (double)block / m_mpv * (mpz_get_ui(m_pbk->n)-1);

        std::cout << "Removing LSB" << std::endl;
        // Remove LSB
        std::bitset<32> bitMsg(shrinkedBlock);
        bitMsg[0] = 0;

        shrinkedBlock = (uint32_t) bitMsg.to_ulong();

        std::cout << "Setting up encryption" << std::endl;
        mpz_t vertBlock, message, embeddedBlock;
        mpz_inits(vertBlock, message, embeddedBlock, NULL);

        mpz_set_ui(vertBlock, shrinkedBlock);
        mpz_set_ui(message, msg);

        std::cout << "Block Encryption" << std::endl;
        pcs_encrypt(m_pbk, m_hr, vertBlock, vertBlock);  // Encrypt vertex data
         std::cout << "Message Encryption" << std::endl;
        pcs_encrypt(m_pbk, m_hr, message, message);  // Encrypt message data 
        //gmp_printf("Vertex = %Zd\nMsg = %Zd\n", vertBlock, message); 

        std::cout << "Embedding" << std::endl;
        pcs_ee_add(m_pbk, embeddedBlock, vertBlock, message);    // Embedding by multiplying block with message 
        std::cout << "Decryption" << std::endl;
        pcs_decrypt(m_pvk, embeddedBlock, embeddedBlock); // Decrypt with private key
        //uint32_t result = mpz2ull(embeddedBlock);

        uint32_t result = mpz_get_ui(embeddedBlock);
        std::cout << "Extracting LSB" << std::endl; // Removing LSB here though not mandatory
        // Remove LSB
        std::bitset<32> bitResult(result);
        bitResult[0] = 0;

        result = (uint32_t) bitResult.to_ulong();

        std::cout << "Expanding" << std::endl;
        //Expand
        result = result / (mpz_get_ui(m_pbk->n)-1) * m_mpv;

        //gmp_printf("Embedding = %Zd\n", embeddedBlock);     // output: c = 126

        // Cleanup all data
        mpz_clears(vertBlock, message, embeddedBlock, NULL);
        pcs_free_public_key(m_pbk);
        pcs_free_private_key(m_pvk);
        hcs_free_random(m_hr);
        std::cout << "Returning result" << std::endl;
        return result;   
    }

    uint32_t Paillier::decrypt(uint64_t msg) const
    {
        return 0;
    }   
}