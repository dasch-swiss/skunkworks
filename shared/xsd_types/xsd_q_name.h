//
// Created by Lukas Rosenthaler on 18.12.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_Q_NAME_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_Q_NAME_H_

#include <string>

#include "xsd_data_type.h"

namespace xsd {

class QName : public DataType {
  /*!
   * Implements the xsd:QName data type
   */
 public:

  /*!
   * Default constructor for QName
   */
  QName() { xsd_type_ = "QName"; }

  /*!
   * Constructor that takes a restriction (shared_ptr) as parameter
   * @param restriction
   */
  inline explicit QName(const std::shared_ptr<Restriction> &restriction) : QName() {
    restrictions_.push_back(restriction);
  }

  /*!
   * Constructor that takes a vector of restrictions (shared_ptr's)  as parameter
   * @param restrictions
   */
  inline explicit QName(const std::vector<std::shared_ptr<Restriction>> &restrictions) : QName() {
    restrictions_ = restrictions;
  }

  /*!
   * Constructor that takes a std::string as parameter
   * @param strval
   */
  explicit QName(const std::string &strval);

  /*!
   * Constructor that takes a std::string and a restriction (shared_ptr) as parameter
   * @param strval
   * @param restriction
   */
  QName(const std::string &strval, const std::shared_ptr<Restriction> &restriction);

  /*!
   * Constructor that takes a string and a vector of restrictions (shared_ptr's) as parameter
   * @param strval
   * @param restrictions
   */
  QName(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  /*!
   * Assignment operator for std::string
   * @param strval
   * @return
   */
  QName &operator=(const std::string &strval) override ;

  /*!
   * Setter with std::string
   * @param strval
   */
  void set(const std::string &strval) override ;

 protected:
  void parse(const std::string &strval);

 private:
  std::string  prefix_;
  std::string  name_;

  std::ostream &print_to_stream(std::ostream &out_stream) const override ;
};

}


#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_Q_NAME_H_
