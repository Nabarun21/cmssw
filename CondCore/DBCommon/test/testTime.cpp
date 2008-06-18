#include "CondCore/DBCommon/interface/Time.h"


#include <iostream>
#include <sys/time.h>
#include "DataFormats/Provenance/interface/Timestamp.h"
int main() {
  ::timeval tv;
  gettimeofday(&tv,0);
  std::cout<<"sec "<<tv.tv_sec<<std::endl;
  std::cout<<"micro sec "<<tv.tv_usec<<std::endl;
  edm::Timestamp tmstamp((unsigned long long)tv.tv_sec*1000000+(unsigned long long)tv.tv_usec);
  std::cout<<"timestamp of the day since 1970 in microsecond "<<tmstamp.value()<<std::endl;
  edm::Timestamp tstamp((unsigned long long)tv.tv_usec);
  std::cout<<"timestamp of the day since 1970 in second "<<tstamp.value()<<std::endl;
  edm::TimeValue_t hlttime=0LL;;
  gettimeofday((timeval*)(&hlttime),0);
  edm::Timestamp hltstamp(hlttime);
  std::cout<<"timestamp of the day since 1970 in HLT "<<hltstamp.value()<<std::endl;
  //  edm::TimeValue_t bizzartime=4294967295LL;
  //usec=bizzartime
  using namespace cond;
  for (size_t i=0; i<TIMETYPE_LIST_MAX; i++) 
    std::cout << "Time Specs:" 
	      << " enum " << timeTypeSpecs[i].type
	      << ", name " << timeTypeSpecs[i].name
	      << ", begin " << timeTypeSpecs[i].beginValue
	      << ", end " << timeTypeSpecs[i].endValue
	      << ", invalid " << timeTypeSpecs[i].invalidValue
	      << std::endl;

  try {
    for (size_t i=0; i<TIMETYPE_LIST_MAX; i++)
      if (cond::findSpecs(timeTypeSpecs[i].name).type!=timeTypeSpecs[i].type)
	std::cout << "error in find for " << timeTypeSpecs[i].name << std::endl;
    
    cond::findSpecs("fake");
  }
  catch(cms::Exception const & e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
