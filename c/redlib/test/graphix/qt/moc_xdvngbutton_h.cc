/****************************************************************************
** XdvngButton meta object code from reading C++ file 'xdvngbutton.h'
**
** Created: Thu Feb 13 03:30:28 2003
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "xdvngbutton.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *XdvngButton::className() const
{
    return "XdvngButton";
}

QMetaObject *XdvngButton::metaObj = 0;

void XdvngButton::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QPushButton::className(), "QPushButton") != 0 )
	badSuperclassWarning("XdvngButton","QPushButton");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString XdvngButton::tr(const char* s)
{
    return qApp->translate( "XdvngButton", s, 0 );
}

QString XdvngButton::tr(const char* s, const char * c)
{
    return qApp->translate( "XdvngButton", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* XdvngButton::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QPushButton::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (XdvngButton::*m1_t0)(bool);
    typedef void (QObject::*om1_t0)(bool);
    m1_t0 v1_0 = &XdvngButton::setCorrect;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "setCorrect(bool)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    typedef void (XdvngButton::*m2_t0)(bool);
    typedef void (QObject::*om2_t0)(bool);
    m2_t0 v2_0 = &XdvngButton::isCorrect;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    QMetaData *signal_tbl = QMetaObject::new_metadata(1);
    signal_tbl[0].name = "isCorrect(bool)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    metaObj = QMetaObject::new_metaobject(
	"XdvngButton", "QPushButton",
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}

// SIGNAL isCorrect
void XdvngButton::isCorrect( bool t0 )
{
    activate_signal_bool( "isCorrect(bool)", t0 );
}
