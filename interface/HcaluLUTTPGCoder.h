#ifndef CALIBCALORIMETRY_HCALTPGALGOS_HCALNOMINALTPGCODER_H
#define CALIBCALORIMETRY_HCALTPGALGOS_HCALNOMINALTPGCODER_H 1

#include "CalibFormats/HcalObjects/interface/HcalTPGCoder.h"
#include "CalibFormats/HcalObjects/interface/HcalNominalCoder.h"
#include "Geometry/CaloTopology/interface/HcalTopology.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include <vector>

/** \class HcaluLUTTPGCoder
  *  
  * The nominal coder uses a user-supplied table to linearize the ADC values.
  *
  * <pre>
  * [number of ieta slices]
  * [low tower 1] [low tower 2] ...
  * [high tower 1] [ high tower 2] ...
  * [LUT 1(0)] [LUT 2(0)] ...
  * [LUT 1(1)] [LUT 2(1)] ...
  * . . .
  * [LUT 1(127)] [LUT 2(127)] ...
  * </pre>
  *
  * $Date: 2007/06/19 21:49:44 $
  * $Revision: 1.11 $
  * \author M. Weinberger -- TAMU
  * \author Tulika Bose and Greg Landsberg -- Brown
  */
class HcaluLUTTPGCoder : public HcalTPGCoder {
public:
  HcaluLUTTPGCoder(const char* filename);
  HcaluLUTTPGCoder(const char* ifilename, const char* ofilename);
  virtual ~HcaluLUTTPGCoder();
  virtual void adc2Linear(const HBHEDataFrame& df, IntegerCaloSamples& ics) const;
  virtual void adc2Linear(const HFDataFrame& df, IntegerCaloSamples& ics) const;
  virtual void compress(const IntegerCaloSamples& ics, const std::vector<bool>& featureBits, HcalTriggerPrimitiveDigi& tp) const;
  virtual void getConditions(const edm::EventSetup& es) const;
  virtual short unsigned int* getLUT(HcalDetId id) const; // returns pointer to the corresponding LUT[128]
  virtual float getPed(HcalDetId id) const;               // returns the PED for channel id
  virtual float getGain(HcalDetId id) const;              // returns the gain for channel id
  virtual void releaseConditions() const {};
  
private:
  static const int nluts = 46007, INPUT_LUT_SIZE = 128;
  int GetLUTID(HcalSubdetector id, int ieta, int iphi, int depth) const;
  void AllocateLUTs();
  void getRecHitCalib(const char* filename);
  float Rcalib[87];
  typedef short unsigned int LUT;
  LUT *inputLUT[nluts];
  float *_gain;
  float *_ped;
  static const float nominal_gain;              // Nominal HB/HE gain in GeV/fC
};
  const float HcaluLUTTPGCoder::nominal_gain = 0.177; 
#endif
