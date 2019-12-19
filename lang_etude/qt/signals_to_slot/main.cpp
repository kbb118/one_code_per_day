#include <stdio.h>
#include <QApplication>
#include <QLineEdit>
#include <QMetaMethod>
#include <QMetaObject>

void ConnectAllSignalsToSlot(QObject * sourceObject, QObject * targetObject, const char * slotName)
{
   const QMetaObject * mo = sourceObject->metaObject();
   if (mo)
   {
      int numMethods = mo->methodCount();
      int firstMethod = mo->methodOffset();  // set to 0 instead if you want to connect signals from superclasses too
      for (int i=firstMethod; i<numMethods; i++)
      {
         QMetaMethod mm = mo->method(i);
         if (mm.methodType() == QMetaMethod::Signal)
         {
            QString signalString = QString("2") + mm.methodSignature();
            printf("Connecting up signal [%s] on object %p to slot [%s] on object %p\n", signalString.toUtf8().constData(), sourceObject, slotName, targetObject);  // just so we can see what it's doing
            QObject::connect(sourceObject, signalString.toUtf8().constData(), targetObject, slotName);
         }
      }
   }
   else printf("Error, sourceObject has no QMetaObject????\n");
}

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);

   QWidget * testSource = new QLineEdit;
   testSource->show();

   ConnectAllSignalsToSlot(testSource, &app, SLOT(quit()));

   return app.exec();
}
