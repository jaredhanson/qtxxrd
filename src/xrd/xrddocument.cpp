#include "xrddocument.h"
#include "xrdxmlns.h"

QTX_BEGIN_NAMESPACE


class XrdDocumentPrivate
{
public:
    XrdDocumentPrivate();
    ~XrdDocumentPrivate();
    
    void addProperty(XrdProperty *prop);
    void addLink(XrdLink *link);
    
    QString id;
    QUrl subject;
    QList<QUrl> aliases;
    XrdPropertyList properties;
    XrdLinkList links;
    QDateTime expires;

    QString characters;
};


QString XrdDocument::mimeType()
{
    return "application/xrd+xml";
}

QString XrdDocument::xmlNamespaceUri()
{
    return kXrdXmlNamespaceUri;
}

QString XrdDocument::xmlName()
{
    return kXrdXmlName;
}

XrdDocument::XrdDocument(QObject *parent /* = 0 */)
    : QObject(parent),
      d_ptr(new XrdDocumentPrivate())
{
}

XrdDocument::~XrdDocument()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

QString XrdDocument::id() const
{
    return d_ptr->id;
}

QUrl XrdDocument::subject() const
{
    return d_ptr->subject;
}

QList<QUrl> XrdDocument::aliases() const
{
    return d_ptr->aliases;
}

XrdPropertyList XrdDocument::properties() const
{
    return d_ptr->properties;
}

XrdLinkList XrdDocument::links() const
{
    return d_ptr->links;
}

bool XrdDocument::isExpired() const
{
    if (!d_ptr->expires.isValid()) {
        return false;
    }

    return (d_ptr->expires < QDateTime::currentDateTime());
}

void XrdDocument::setId(const QString & id)
{
    d_ptr->id = id;
}

void XrdDocument::setSubject(const QUrl & subject)
{
    d_ptr->subject = subject;
}

void XrdDocument::addAlias(const QUrl & alias)
{
    d_ptr->aliases.append(alias);
}

void XrdDocument::addProperty(XrdProperty *prop)
{
    prop->setParent(this);
    d_ptr->addProperty(prop);
}

void XrdDocument::addLink(XrdLink *link)
{
    link->setParent(this);
    d_ptr->addLink(link);
}

void XrdDocument::setExpires(const QDateTime & dateTime)
{
    d_ptr->expires = dateTime;
}

IXmlDeserializing *XrdDocument::deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    Q_UNUSED(attributes)
    
    if (namespaceUri == XrdLink::xmlNamespaceUri() && name == XrdLink::xmlName()) {
        XrdLink* link = new XrdLink(this);
        d_ptr->addLink(link);
        return link;
    } else if (namespaceUri == XrdProperty::xmlNamespaceUri() && name == XrdProperty::xmlName()) {
        XrdProperty* prop = new XrdProperty(this);
        d_ptr->addProperty(prop);
        return prop;
    }

    return this;
}

void XrdDocument::deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri)
{
    Q_UNUSED(deserializer)
    
    if (namespaceUri == xmlNamespaceUri() && name == kXrdSubjectXmlName) {
        d_ptr->subject = d_ptr->characters.trimmed();
    } else if (namespaceUri == xmlNamespaceUri() && name == kXrdAliasXmlName) {
        d_ptr->aliases.append(d_ptr->characters.trimmed());
    } else if (namespaceUri == xmlNamespaceUri() && name == kXrdExpiresXmlName) {
        d_ptr->expires = QDateTime::fromString(d_ptr->characters.trimmed(), Qt::ISODate);
    }

    d_ptr->characters.clear();
}

void XrdDocument::deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes)
{
    Q_UNUSED(deserializer)
    
    d_ptr->id = attributes.value("xml:id").toString();
}

void XrdDocument::deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text)
{
    Q_UNUSED(deserializer)
    
    d_ptr->characters.append(text);
}


XrdDocumentPrivate::XrdDocumentPrivate()
{
}

XrdDocumentPrivate::~XrdDocumentPrivate()
{
}

void XrdDocumentPrivate::addProperty(XrdProperty *prop)
{
    properties.append(prop);
}

void XrdDocumentPrivate::addLink(XrdLink *link)
{
    links.append(link);
}


QTX_END_NAMESPACE
