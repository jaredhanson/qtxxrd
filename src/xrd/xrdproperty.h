#ifndef QTXXRD_PROPERTY_H
#define QTXXRD_PROPERTY_H

#include "xrdglobal.h"
#include <QtxXml>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class XrdPropertyPrivate;

class XrdProperty : public QObject,
                    public IXmlDeserializing
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
    
    
    virtual IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes);
    virtual void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri);
    virtual void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    virtual void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);
    
protected:
    XrdPropertyPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(XrdProperty);
};


QTX_END_NAMESPACE

#endif // QTXXRD_PROPERTY_H
