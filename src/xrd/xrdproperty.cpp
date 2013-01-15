#include "xrdproperty.h"
#include "xrdxmlns.h"

QTX_BEGIN_NAMESPACE


class XrdPropertyPrivate
{
public:
    XrdPropertyPrivate();
    ~XrdPropertyPrivate();
    
    QString type;
    QString value;
};


QString XrdProperty::xmlNamespaceUri()
{
    return kXrdXmlNamespaceUri;
}

QString XrdProperty::xmlName()
{
    return kXrdPropertyXmlName;
}

XrdProperty::XrdProperty(QObject *parent /* = 0 */)
    : QObject(parent),
      d_ptr(new XrdPropertyPrivate())
{
}

XrdProperty::~XrdProperty()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

QString XrdProperty::type() const
{
    return d_ptr->type;
}

QString XrdProperty::value() const
{
    return d_ptr->value;
}

void XrdProperty::setType(const QString & type)
{
    d_ptr->type = type;
}

void XrdProperty::setValue(const QString & value)
{
    d_ptr->value = value;
}

void XrdProperty::deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    
    d_ptr->type = attributes.value("type").toString();
}

void XrdProperty::deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text)
{
    Q_UNUSED(deserializer)

    d_ptr->value.append(text);
}

void XrdProperty::serializeXml(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(XrdProperty::xmlNamespaceUri(), XrdProperty::xmlName());
    writer->writeAttribute("type", d_ptr->type);
    writer->writeCharacters(d_ptr->value);
    writer->writeEndElement();
}


XrdPropertyPrivate::XrdPropertyPrivate()
{
}

XrdPropertyPrivate::~XrdPropertyPrivate()
{
}


QTX_END_NAMESPACE
