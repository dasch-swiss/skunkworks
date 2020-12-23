//
// Created by Lukas Rosenthaler on 27.11.20.
//

#ifndef SKUNKWORKS_HELPERS_ERROR_H_
#define SKUNKWORKS_HELPERS_ERROR_H_

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

namespace dsp {

class Error : std::runtime_error {
 protected:
  int line;            //!< Linenumber where the exception has been throwns
  std::string file;    //!< Name of source code file where the exception has been thrown
  std::string message; //!< Description of the problem
  int sysErrno;        //!< If there is a system error number

 public:

  inline int getLine(void) const { return line; }

  inline std::string getFile(void) const { return file; }

  inline std::string getMessage(void) const { return message; }

  inline int getSysErrno(void) const { return sysErrno; }

  /*!
  * Constructor with all (char *) strings
  *
  * \param[in] file The filename, usually the __FILE__ macro.
  * \param[in] line The source code line, usually the __LINE__ macro.
  * \param[in] msg The message describing the error.
  * \param[in] errno_p Retrieve and display the system error message from errno.
  */
  Error(const char *file, const int line, const char *msg, int errno_p = 0);

  /*!
  * Constructor with std::string strings for the message. The file parameter is
  * is always of type (char *), becuase usually its either __LINE__ or a static
  * pointer to char
  *
  * \param[in] file The filename, usually the __FILE__ macro.
  * \param[in] line The source code line, usually the __LINE__ macro.
  * \param[in] msg The message describing the error.
  * \param[in] syserr Retrieve and display the system error message from errno.
  */
  Error(const char *file, const int line, const std::string &msg, int errno_p = 0);

  inline ~Error() throw() {};

  /*!
   * Returns the error as a one-line string
   *
   * \returns Error string
   */
  std::string to_string(void) const;

  inline operator std::string() const {
    return to_string();
  }

  /*!
  * The overloaded << operator which is used to write the error message to the output
  *
  * \param[in] outStream The output stream
  * \param[in] rhs Reference to an instance of a Error
  * \returns Returns an std::ostream object
  */
  friend std::ostream &operator<<(std::ostream &outStream, const Error &rhs);
};

};
#endif //SKUNKWORKS_HELPERS_ERROR_H_
