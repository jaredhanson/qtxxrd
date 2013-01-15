#include "tst_xrdproperty.h"
#include "xrdproperty.h"


void tst_XrdProperty::init()
{
    mDeserializer = new XmlDeserializer();
    mDeserializer->setDelegate(this);
    
    mProperty = 0;
}

void tst_XrdProperty::cleanup()
{
    if (mProperty) {
        delete mProperty;
        mProperty = 0;
    }

    if (mDeserializer) {
        delete mDeserializer;
        mDeserializer = 0;
    }
}

void tst_XrdProperty::readElement()
{
    QFile file("data/element.xml");
    file.open(QIODevice::ReadOnly);
    
    mDeserializer->addData(file.readAll());
    mDeserializer->parse();

    QVERIFY(mProperty);
    QCOMPARE(mProperty->type(), QString("http://spec.example.net/version"));
    QCOMPARE(mProperty->value(), QString("1.0"));
}

IXmlDeserializing* tst_XrdProperty::deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(attributes)

    if (namespaceUri == XrdProperty::xmlNamespaceUri() && name == XrdProperty::xmlName()) {
        mProperty = new XrdProperty();
        return mProperty;
    }
    
    return 0;
}

void tst_XrdProperty::deserializeXmlEnd(XmlDeserializer *deserializer)
{
    Q_UNUSED(deserializer)
}

void tst_XrdProperty::deserializeXmlError(XmlDeserializer *deserializer, const QXmlStreamReader::Error error, const QString & errorString)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(error)
    Q_UNUSED(errorString)
}

void tst_XrdProperty::writeElement()
{
    QString output;
    QXmlStreamWriter writer(&output);
    XrdProperty property;
    property.setType("http://spec.example.net/version");
    property.setValue("1.0");
    property.serializeXml(&writer);
    
    QCOMPARE(output, QString("<n1:Property xmlns:n1=\"http://docs.oasis-open.org/ns/xri/xrd-1.0\" type=\"http://spec.example.net/version\">1.0</n1:Property>"));
}


QTEST_APPLESS_MAIN(tst_XrdProperty)
