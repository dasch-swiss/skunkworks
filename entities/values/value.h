//
// Created by Lukas Rosenthaler on 26.11.20.
//

#ifndef SKUNKWORKS_VALUE_H
#define SKUNKWORKS_VALUE_H

#include "helpers/xsd_types/error.h"
#include "helpers/xsd_types/date_time_stamp.h"
#include "helpers/xsd_types/lang_string.h"
#include "helpers/xsd_types/others.h"

#include "agent.h"

class Value {
private:
    xsd::DateTimeStamp creation_date_;
    std::shared_ptr<dsp::Agent> created_by_;
    xsd::boolean is_deleted_;
    xsd::DateTimeStamp delete_date_;
    std::shared_ptr<dsp::Agent> deleted_by_;
    xsd::langstring delete_comment_;
    xsd::langstring comment_;
    xsd::string strval;
public:
    /**
     * Getter for creation_date
     *
     * @return xsd::DateTimeStamp
     */
    inline xsd::DateTimeStamp creation_date() {
        return creation_date_;
    }

    /**
     * Setter for creation_date
     *
     * @param creation_date xsd::DateTimeStamp
     */
    inline void creation_date(const xsd::DateTimeStamp &creation_date) {
        creation_date_ = creation_date;
    }

    /**
     * Setter for creation date
     * @param creation_date std::string with correct xsd formatting!
     */
    inline void creation_date(const std::string &creation_date) {
        creation_date_ = xsd::DateTimeStamp(creation_date)
    }

    /**
     * Delete the value
     *
     * @param deleted_by The Agent deleting the value
     */
    void delete(const shared_ptr<Agent> deleted_by);

    /**
     * Delete the value
     *
     * @param deleted_by The Agent deleting the value
     * @param delete_comment xsd::LangString Comment why the value is being deleted
     */
    void delete(const shared_ptr<Agent> deleted_by, const xsd::LangString delete_comment);

    /**
     * Delete the value
     *
     * @param deleted_by The Agent deleting the value
     * @param lang Language of the comment
     * @param delete_comment std::string Comment why the value is being deleted
     */
    delete(const shared_ptr<Agent> deleted_by, Language lang, const std::string &delete_comment);

    virtual std::string to_string() = 0;
}


#endif //SKUNKWORKS_VALUE_H
