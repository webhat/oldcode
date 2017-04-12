/****************************************************************************
** Xdvng meta object code from reading C++ file 'xdvng.h'
**
** Created: Thu Feb 13 03:30:34 2003
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "xdvng.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *Xdvng::className() const
{
    return "Xdvng";
}

QMetaObject *Xdvng::metaObj = 0;

void Xdvng::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("Xdvng","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString Xdvng::tr(const char* s)
{
    return qApp->translate( "Xdvng", s, 0 );
}

QString Xdvng::tr(const char* s, const char * c)
{
    return qApp->translate( "Xdvng", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* Xdvng::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (Xdvng::*m1_t0)(int);
    typedef void (QObject::*om1_t0)(int);
    m1_t0 v1_0 = &Xdvng::setCorrect;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "setCorrect(int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    typedef void (Xdvng::*m2_t0)(int);
    typedef void (QObject::*om2_t0)(int);
    m2_t0 v2_0 = &Xdvng::isCorrect;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    QMetaData *signal_tbl = QMetaObject::new_metadata(1);
    signal_tbl[0].name = "isCorrect(int)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    metaObj = QMetaObject::new_metaobject(
	"Xdvng", "QWidget",
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
void Xdvng::isCorrect( int t0 )
{
    activate_signal( "isCorrect(int)", t0 );
}
