#ifndef QTXXRD_DOCUMENT_H
#define QTXXRD_DOCUMENT_H

#include "xrdglobal.h"
#include "xrdproperty.h"
#include "xrdlink.h"
#include <QtxXml>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class XrdDocumentPrivate;

class XrdDocument : public QObject,
                    public IXmlDeserializing
{
    Q_OBJECT
    
public:
    static QString mimeType();
    static QString xmlNamespaceUri();
    static QString xmlName();
    
public:
    XrdDocument(QObject *parent = 0);
    ~XrdDocument();
    
    QString id() const;
    QUrl subject() const;
    QList<QUrl> aliases() const;
    XrdPropertyList properties() const;
    XrdLinkList links() const;
    bool isExpired() const;
    
    void setId(const QString & id);
    void setSubject(const QUrl & subject);
    void addAlias(const QUrl & alias);
    void addProperty(XrdProperty *prop);
    void addLink(XrdLink *link);
    void setExpires(const QDateTime & dateTime);
    
    
    virtual IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes);
    virtual void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name);
    virtual void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    virtual void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);
    
protected:
    XrdDocumentPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(XrdDocument);
};


QTX_END_NAMESPACE

#endif // QTXXRD_DOCUMENT_H
