#ifndef PAILLIER_HPP
#define PAILLIER_HPP

#include <cmath>
#include <cstdint>
#include <libhcs.h>
#include <gmp.h>
#include <bitset>

namespace encrypt3d {

    class Paillier{
    public :
        explicit Paillier(int l);
        uint32_t encrypt(uint32_t block, unsigned int msg) const;
        uint32_t decrypt(uint64_t msg) const;
        
        int l() const { return m_l; }
        uint64_t mpv() const { return m_mpv; }
        

    private:
        pcs_public_key *m_pbk;
        pcs_private_key *m_pvk;
        hcs_random *m_hr;
        uint64_t m_mpv;
        int m_l;
    };

}

#endif