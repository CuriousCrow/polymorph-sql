#ifndef QFILEUTILS_H
#define QFILEUTILS_H

#include <QFile>
#include <QDir>
#include <QStringList>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>

class QFileUtils
{
public:
  QFileUtils();
  //Загрука файла в строку
  static QString fileToString(QString filepath, bool isUtf8 = true);
  //
  static QByteArray loadFile(QString filepath);
  //Сохранение строки в файл
  static bool stringToFile(QString str, QString filepath, bool isUtf = true);
  //Транслитерация строки
  static QString transliterate(QString& inStr);
  //
  static bool forcePath(const QString &path);

  static QString extractDirPath(const QString &fullPath);

  static QString extractFileName(const QString &fullPath);

  static QString mimeFromExtension(QString filename);

  static bool saveFile(const QString &filepath, const QByteArray &data);

  static bool copyDirectory(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
};

class QFilePath
{
public:
  QFilePath(QString fullpath);
  QString extension();
  QString folderPath();
  QString filename();
  bool isFolder();

  static QString extension(const QString &path);
  static QString folderPath(const QString &path);
  static QString filename(const QString &path);
  static bool isFolder(const QString &path);
private:
  QString _fullPath;
  QString _extension;
  QString _filename;
  QString _folderPath;
};

#endif // QFILEUTILS_H
