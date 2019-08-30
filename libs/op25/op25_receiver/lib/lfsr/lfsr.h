/*
 * lfsr.h
 *
 * Translation of lfsr.py to c++ - header file
 *
 *  Created on: Feb 19, 2017
 *      Author: S. Lukic
 */

#ifndef LFSR_H_
#define LFSR_H_


#include "Eigen/Dense"

class p25p2_lfsr {
public:
  p25p2_lfsr(unsigned nac, unsigned sysid, unsigned wacn);

  const Eigen::VectorXi * getXorsyms() const { return xorsyms; }
  const char * getXorChars(unsigned &len) const;

private:

  Eigen::VectorXi * mk_xor_bits(unsigned long, unsigned long, unsigned long);

  static long unsigned asm_reg( long unsigned s[6] );
  static long unsigned * disasm_reg(long unsigned r);
  static long unsigned cyc_reg(long unsigned reg);

  Eigen::VectorXi *xorsyms;
  std::string *xor_chars;

  static const int msize = 44;
  Eigen::Matrix<int, msize, msize> M;

};








#endif /* LFSR_H_ */
