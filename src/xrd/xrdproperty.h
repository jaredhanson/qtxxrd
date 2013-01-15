#ifndef QTXXRD_PROPERTY_H
#define QTXXRD_PROPERTY_H

#include "xrdglobal.h"
#include <QtxXml>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class XrdPropertyPrivate;

class XrdProperty : public QObject,
                    public IXmlDeserializing,
                    public IXmlSerializing
{
    Q_OBJECT
    
public:
    static QString xmlNamespaceUri();
    static QString xmlName();
    
public:
    XrdProperty(QObject *parent = 0);
    ~XrdProperty();
    
    QString type() const;
    QString value() const;

    void setType(const QString & type);
    void setValue(const QString & value);
    
    
    virtual void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    virtual void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);
    
    virtual void serializeXml(QXmlStreamWriter *writer) const;
    
protected:
    XrdPropertyPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(XrdProperty);
};

typedef QList<XrdProperty *> XrdPropertyList;


QTX_END_NAMESPACE

#endif // QTXXRD_PROPERTY_H
