#include <iostream>
#include "paillierBlock.hpp"

namespace encrypt3d {

  // double : 12 bits to skip
  PaillierBlock PaillierBlock::fromFloat(float value)
  {
    PaillierBlock c;
    c.m_float = value;
    c.m_uint32 = *reinterpret_cast<uint32*>(&value);
    return c;
  }

  PaillierBlock PaillierBlock::fromUint32(uint32 value)
  {
    PaillierBlock c;
    c.m_uint32 = value;
    c.m_float = *reinterpret_cast<float*>(&value);
    return c;
  }

  PaillierBlock PaillierBlock::mantisse() const
  {
    return PaillierBlock::fromUint32(get_n_bits_(m_uint32, 9, 23));
  }

  PaillierBlock PaillierBlock::remplaceMantisse(const PaillierBlock& m) const
  {
    uint32 v = remplace_n_bits_(m_uint32, 9, 23, m.toUint32());
    return PaillierBlock::fromUint32(v);
  }

  PaillierBlock PaillierBlock::encrypteMantisse(int n, const Paillier& paillier, int msg) const
  {
    if (n <= 0) { return *this; }
    uint32 m = get_n_bits_(m_uint32, 9, n);
    uint32 l = 32 - ((9 + (unsigned)n) > 32 ? 32 : (9 +(unsigned)n));
    //std::cout << l << std::endl;
    //std::cout << "E  : " << std::bitset<32>(m) << " " << m << std::endl;
    m >>= l;
    //std::cout << "E- : " << std::bitset<32>(m) << " " << m << std::endl;
    uint32_t encryptedMantissa = paillier.encrypt(m, msg);
    //std::cout << "EE : " << std::bitset<64>(encryptedMantissa) << " " << encryptedMantissa << std::endl;
    encryptedMantissa <<= l;
    //std::cout << "EE-: " << std::bitset<32>(mc) << " " << mc << std::endl;

    return PaillierBlock::fromUint32(remplace_n_bits_(m_uint32, 9, n, encryptedMantissa));
  }

  PaillierBlock PaillierBlock::decrypteMantisse(int n, const Paillier& paillier) const
  {
    if (n <= 0) { return *this; }
    uint32 m = get_n_bits_(m_uint32, 9, n);
    //std::cout << "D  : " << std::bitset<32>(m) << " " << m << std::endl;
    uint32 l = 32 - ((9 + (unsigned)n) > 32 ? 32 : (9 +(unsigned)n));
    m >>= l;
    //std::cout << "D- : " << m << std::endl;
    uint32 mc = paillier.decrypt(m);
    //std::cout << "DD : " << std::bitset<32>(mc) << " " << mc << std::endl;
    mc <<= l;
    //std::cout << "DD-: " << std::bitset<32>(mc) << " " << mc << std::endl;

    return PaillierBlock::fromUint32(remplace_n_bits_(m_uint32, 9, n, mc));
  }

  PaillierBlock PaillierBlock::insereMessageLSB(int n, uint32 value) const
  {
    if (n <= 0) { return *this; }
    return PaillierBlock::fromUint32(remplace_n_bits_(m_uint32, (32-n), n, value));
  }

  PaillierBlock PaillierBlock::retireMessageLSB(int n) const
  {
    if (n <= 0) { return *this; }
    return PaillierBlock::fromUint32(get_n_bits_(m_uint32, (32-n), n));
  }

  uint32 PaillierBlock::get_n_bits_(uint32 f, int beg, int n)
  {
    if (n <= 0 || beg < 0 || beg > 32) {
      return 0;
    }
    uint32 masque = (0xFFFFFFFF >> (unsigned)beg) & (0xFFFFFFFF << (unsigned)(32 - ((beg+n)>32?32:(beg+n))));
    return f & masque;
  }

  uint32 PaillierBlock::remplace_n_bits_(uint32 f, int beg, int n, uint32 val)
  {
    uint32 pre = get_n_bits_(f, 0, beg);
    uint32 post = get_n_bits_(f, beg + n, 32 - beg - n);
    return (val | pre | post);
  }

  std::ostream& operator<<(std::ostream& os, const PaillierBlock& c)
  {
    os << std::bitset<32>(c.toUint32()) << std::endl;
    return os;
  }
}
