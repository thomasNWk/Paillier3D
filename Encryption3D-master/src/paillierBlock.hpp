#ifndef MINIPROJET_PAILLIERBLOCK_HPP
#define MINIPROJET_PAILLIERBLOCK_HPP

#include <cstdint>
#include <bitset>
#include "rsa.hpp"
#include "paillier.hpp"

namespace encrypt3d {
  
  typedef uint32_t uint32;

  class PaillierBlock {
  private:
    float    m_float {};
    uint32 m_uint32 {};

    uint64_t m_integer64b {};

  public:
    PaillierBlock() = default;

    float toFloat() const { return m_float; }
    uint32 toUint32() const { return m_uint32; }

    static PaillierBlock fromFloat(float value);

    static PaillierBlock fromUint32(uint32 value);

    PaillierBlock mantisse() const;

    PaillierBlock remplaceMantisse(const PaillierBlock& m) const;

    PaillierBlock encrypteMantisse(int n, const Paillier& paillier, int msg) const;
    PaillierBlock decrypteMantisse(int n, const Paillier& paillier) const;

    PaillierBlock insereMessageLSB(int n, uint32 value) const;
    PaillierBlock retireMessageLSB(int n) const;

  private:
    static uint32 get_n_bits_(uint32 f, int beg, int n);
    static uint32 remplace_n_bits_(uint32 f, int beg, int n, uint32 val);
  };

  std::ostream& operator<<(std::ostream& os, const PaillierBlock& c);
}


#endif //MINIPROJET_PAILLIERBLOCK_HPP
