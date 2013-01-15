#ifndef TST_XRDPROPERTY_H
#define TST_XRDPROPERTY_H

#include "xrdproperty.h"
#include <QtxXml>
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_XrdProperty : public QObject,
                        public IXmlDeserializerDelegate
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    
    void readElement();
    
    void writeElement();
    
protected:
    virtual IXmlDeserializing* deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes);
    virtual void deserializeXmlEnd(XmlDeserializer *deserializer);
    virtual void deserializeXmlError(XmlDeserializer *deserializer, const QXmlStreamReader::Error error, const QString & errorString);
    
private:
    XmlDeserializer *mDeserializer;
    XrdProperty *mProperty;
};

#endif // TST_XRDPROPERTY_H
