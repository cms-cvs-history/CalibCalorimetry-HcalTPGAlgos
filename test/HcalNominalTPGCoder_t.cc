#include "CalibCalorimetry/HcalTPGAlgos/interface/HcalNominalTPGCoder.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/HcalTowerAlgo/interface/HcalHardcodeGeometryLoader.h"
#include <iostream>

int main() {

  HcalHardcodeGeometryLoader l;
  const CaloSubdetectorGeometry* sg=l.load().release();
  
  CaloGeometry geom;
  geom.setSubdetGeometry(DetId::Hcal,HcalBarrel,sg);
  geom.setSubdetGeometry(DetId::Hcal,HcalEndcap,sg);
  geom.setSubdetGeometry(DetId::Hcal,HcalForward,sg);
  geom.setSubdetGeometry(DetId::Hcal,HcalOuter,sg);

  HcalNominalTPGCoder coder(0.125); // 125 MeV LSB

  coder.setupGeometry(geom);

  HcalDetId id(HcalBarrel,1,1,1);
  HBHEDataFrame f1(id);
  f1.setSize(10);
  f1.setSample(0, HcalQIESample(5,0,1,1));
  f1.setSample(1, HcalQIESample(4,1,1,1));
  f1.setSample(2, HcalQIESample(5,2,1,1));
  f1.setSample(3, HcalQIESample(6,3,1,1));
  f1.setSample(4, HcalQIESample(28,0,1,1));
  f1.setSample(5, HcalQIESample(36,1,1,1));
  f1.setSample(6, HcalQIESample(12,2,1,1));
  f1.setSample(7, HcalQIESample(8,3,1,1));
  f1.setSample(8, HcalQIESample(5,0,1,1));
  f1.setSample(9, HcalQIESample(6,1,1,1));

  const float gain[4]={0.20,0.20,0.20,0.20};
  const float peds[4]={5,5,5,5};
  HcalCalibrations calib(gain,peds);
  
  coder.setupForChannel(calib);

  IntegerCaloSamples ics;
  coder.adc2ET(f1,ics);
  std::cout << f1 << std::endl <<ics <<std::endl;

  for (int ieta=2; ieta<=29; ieta++) {
    HcalDetId id2(((ieta<=16)?(HcalBarrel):(HcalEndcap)),ieta,ieta*2-1,1);
    HBHEDataFrame f2(id2);
    f2.setSize(10);
    for (int i=0; i<10; i++) f2.setSample(i,f1[i]);
    coder.adc2ET(f2,ics);
    std::cout << id2 << std::endl <<ics <<std::endl;
  }

}
