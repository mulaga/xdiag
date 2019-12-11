// Copyright 2018 Alexander Wietek - All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "bond.h"

namespace hydra { namespace operators {

    Bond::Bond(const std::string& type, const std::string& coupling, 
	       const std::vector<int>& sites)
      : type_(type), 
	coupling_(coupling), 
	sites_(sites), 
	has_parameters_(false),
	parameters_()
    {}

    Bond::Bond(const std::string& type, const std::string& coupling, 
	       const std::vector<int>& sites, 
	       const parameters::Parameters& parameters)
      : type_(type), 
	coupling_(coupling), 
	sites_(sites),
	has_parameters_(true),
	parameters_(parameters)
    {}

    std::ostream& operator<< (std::ostream& out, const Bond& bond)
    {
      out << bond.type() << " " << bond.coupling() << " ";
      for (auto site : bond.sites()) out << site << " ";
      return out;
    }

    bool operator==(const Bond& lhs, const Bond& rhs)  
    {
      return (lhs.type() == rhs.type()) && (lhs.coupling() == rhs.coupling()) &&
	(lhs.sites() == rhs.sites());
    }

    TypeCoupling::TypeCoupling(const std::string& type, 
			       const std::string& coupling)
      : type_(type), coupling_(coupling)
    {}

    std::ostream& operator<< (std::ostream& out, const TypeCoupling& tc)
    {
      out << tc.type() << " " << tc.coupling() << " ";
      return out;
    }

    bool operator ==(const TypeCoupling& tc1, const TypeCoupling& tc2)
    { return (tc1.type() == tc2.type()) && (tc1.coupling() == tc2.coupling()); }

    TypeCoupling type_coupling(const Bond& bond)
    { return TypeCoupling(bond.type(), bond.coupling()); }

  }
}
