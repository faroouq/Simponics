//
// Generated file, do not edit! Created by nedtool 5.6 from sensoryMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "sensoryMsg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace simponics {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(sensoryMsg)

sensoryMsg::sensoryMsg(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->entries = 0;
    this->source = 0;
    this->destination = 0;
    for (unsigned int i=0; i<10; i++)
        this->dataValue[i] = 0;
    for (unsigned int i=0; i<10; i++)
        this->dataStdValue[i] = 0;
    this->txTime = 0;
}

sensoryMsg::sensoryMsg(const sensoryMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

sensoryMsg::~sensoryMsg()
{
}

sensoryMsg& sensoryMsg::operator=(const sensoryMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void sensoryMsg::copy(const sensoryMsg& other)
{
    this->entries = other.entries;
    this->source = other.source;
    this->destination = other.destination;
    this->payload = other.payload;
    for (unsigned int i=0; i<10; i++)
        this->dataName[i] = other.dataName[i];
    for (unsigned int i=0; i<10; i++)
        this->dataValue[i] = other.dataValue[i];
    for (unsigned int i=0; i<10; i++)
        this->dataStdValue[i] = other.dataStdValue[i];
    this->txTime = other.txTime;
}

void sensoryMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->entries);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->payload);
    doParsimArrayPacking(b,this->dataName,10);
    doParsimArrayPacking(b,this->dataValue,10);
    doParsimArrayPacking(b,this->dataStdValue,10);
    doParsimPacking(b,this->txTime);
}

void sensoryMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->entries);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->payload);
    doParsimArrayUnpacking(b,this->dataName,10);
    doParsimArrayUnpacking(b,this->dataValue,10);
    doParsimArrayUnpacking(b,this->dataStdValue,10);
    doParsimUnpacking(b,this->txTime);
}

int sensoryMsg::getEntries() const
{
    return this->entries;
}

void sensoryMsg::setEntries(int entries)
{
    this->entries = entries;
}

int sensoryMsg::getSource() const
{
    return this->source;
}

void sensoryMsg::setSource(int source)
{
    this->source = source;
}

int sensoryMsg::getDestination() const
{
    return this->destination;
}

void sensoryMsg::setDestination(int destination)
{
    this->destination = destination;
}

const char * sensoryMsg::getPayload() const
{
    return this->payload.c_str();
}

void sensoryMsg::setPayload(const char * payload)
{
    this->payload = payload;
}

unsigned int sensoryMsg::getDataNameArraySize() const
{
    return 10;
}

const char * sensoryMsg::getDataName(unsigned int k) const
{
    if (k>=10) throw omnetpp::cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    return this->dataName[k].c_str();
}

void sensoryMsg::setDataName(unsigned int k, const char * dataName)
{
    if (k>=10) throw omnetpp::cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    this->dataName[k] = dataName;
}

unsigned int sensoryMsg::getDataValueArraySize() const
{
    return 10;
}

double sensoryMsg::getDataValue(unsigned int k) const
{
    if (k>=10) throw omnetpp::cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    return this->dataValue[k];
}

void sensoryMsg::setDataValue(unsigned int k, double dataValue)
{
    if (k>=10) throw omnetpp::cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    this->dataValue[k] = dataValue;
}

unsigned int sensoryMsg::getDataStdValueArraySize() const
{
    return 10;
}

double sensoryMsg::getDataStdValue(unsigned int k) const
{
    if (k>=10) throw omnetpp::cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    return this->dataStdValue[k];
}

void sensoryMsg::setDataStdValue(unsigned int k, double dataStdValue)
{
    if (k>=10) throw omnetpp::cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    this->dataStdValue[k] = dataStdValue;
}

double sensoryMsg::getTxTime() const
{
    return this->txTime;
}

void sensoryMsg::setTxTime(double txTime)
{
    this->txTime = txTime;
}

class sensoryMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    sensoryMsgDescriptor();
    virtual ~sensoryMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(sensoryMsgDescriptor)

sensoryMsgDescriptor::sensoryMsgDescriptor() : omnetpp::cClassDescriptor("simponics::sensoryMsg", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

sensoryMsgDescriptor::~sensoryMsgDescriptor()
{
    delete[] propertynames;
}

bool sensoryMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<sensoryMsg *>(obj)!=nullptr;
}

const char **sensoryMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *sensoryMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int sensoryMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int sensoryMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *sensoryMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "entries",
        "source",
        "destination",
        "payload",
        "dataName",
        "dataValue",
        "dataStdValue",
        "txTime",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int sensoryMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "entries")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataName")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataValue")==0) return base+5;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataStdValue")==0) return base+6;
    if (fieldName[0]=='t' && strcmp(fieldName, "txTime")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *sensoryMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "string",
        "string",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **sensoryMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *sensoryMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int sensoryMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    sensoryMsg *pp = (sensoryMsg *)object; (void)pp;
    switch (field) {
        case 4: return 10;
        case 5: return 10;
        case 6: return 10;
        default: return 0;
    }
}

const char *sensoryMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    sensoryMsg *pp = (sensoryMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string sensoryMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    sensoryMsg *pp = (sensoryMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getEntries());
        case 1: return long2string(pp->getSource());
        case 2: return long2string(pp->getDestination());
        case 3: return oppstring2string(pp->getPayload());
        case 4: return oppstring2string(pp->getDataName(i));
        case 5: return double2string(pp->getDataValue(i));
        case 6: return double2string(pp->getDataStdValue(i));
        case 7: return double2string(pp->getTxTime());
        default: return "";
    }
}

bool sensoryMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    sensoryMsg *pp = (sensoryMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setEntries(string2long(value)); return true;
        case 1: pp->setSource(string2long(value)); return true;
        case 2: pp->setDestination(string2long(value)); return true;
        case 3: pp->setPayload((value)); return true;
        case 4: pp->setDataName(i,(value)); return true;
        case 5: pp->setDataValue(i,string2double(value)); return true;
        case 6: pp->setDataStdValue(i,string2double(value)); return true;
        case 7: pp->setTxTime(string2double(value)); return true;
        default: return false;
    }
}

const char *sensoryMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *sensoryMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    sensoryMsg *pp = (sensoryMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace simponics

