#include "xrdlink.h"
#include "xrdxmlns.h"

QTX_BEGIN_NAMESPACE


class XrdLinkPrivate
{
public:
    XrdLinkPrivate();
    ~XrdLinkPrivate();
    
    void addProperty(XrdProperty *prop);
    
    QUrl href;
    QString type;
    QString rel;
    QString templ8;
    QString title;
    XrdPropertyList properties;
    
    QString characters;
};


QString XrdLink::xmlNamespaceUri()
{
    return kXrdXmlNamespaceUri;
}

QString XrdLink::xmlName()
{
    return kXrdLinkXmlName;
}

XrdLink::XrdLink(QObject *parent /* = 0 */)
    : QObject(parent),
      d_ptr(new XrdLinkPrivate())
{
}

XrdLink::~XrdLink()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

QString XrdLink::rel() const
{
    return d_ptr->rel;
}

QString XrdLink::type() const
{
    return d_ptr->type;
}

QUrl XrdLink::href() const
{
    return d_ptr->href;
}

QString XrdLink::uriTemplate() const
{
    return d_ptr->templ8;
}

QString XrdLink::title() const
{
    return d_ptr->title;
}

XrdPropertyList XrdLink::properties() const
{
    return d_ptr->properties;
}

void XrdLink::setHref(const QUrl & url)
{
    d_ptr->href = url;
}

void XrdLink::setType(const QString & type)
{
    d_ptr->type = type;
}

void XrdLink::setRel(const QString & rel)
{
    d_ptr->rel = rel;
}

void XrdLink::setUriTemplate(const QString & uriTemplate)
{
    d_ptr->templ8 = uriTemplate;
}

void XrdLink::setTitle(const QString & title)
{
    d_ptr->title = title;
}

IXmlDeserializing *XrdLink::deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(attributes)
    
    if (namespaceUri == XrdProperty::xmlNamespaceUri() && name == XrdProperty::xmlName()) {
        XrdProperty *prop = new XrdProperty(this);
        d_ptr->addProperty(prop);
        return prop;
    }

    return this;
}

void XrdLink::deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name)
{
    Q_UNUSED(deserializer)
    
    if (namespaceUri == xmlNamespaceUri() && name == kXrdTitleXmlName) {
        d_ptr->title = d_ptr->characters.trimmed();
    }

    d_ptr->characters.clear();
}

void XrdLink::deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    
    d_ptr->href = attributes.value("href").toString();
    d_ptr->type = attributes.value("type").toString();
    d_ptr->rel = attributes.value("rel").toString();
    d_ptr->templ8 = attributes.value("template").toString();
}

void XrdLink::deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text)
{
    Q_UNUSED(deserializer)

    d_ptr->characters.append(text);
}


XrdLinkPrivate::XrdLinkPrivate()
{
}

XrdLinkPrivate::~XrdLinkPrivate()
{
}

void XrdLinkPrivate::addProperty(XrdProperty *prop)
{
    properties.append(prop);
}


QTX_END_NAMESPACE
