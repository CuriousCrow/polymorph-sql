#include "qfileutils.h"

QFileUtils::QFileUtils()
{
}

QString QFileUtils::fileToString(QString filepath, bool isUtf8)
{
  QFile file(filepath);
  if (!file.exists()){
    qWarning() << "File" << file.fileName() << "doesn't exists";
    return "";
  }
  file.open(QIODevice::ReadOnly);
  QString result;
  if (isUtf8){
    result = QString::fromUtf8(file.readAll());
  }
  else {
    result = QString::fromLocal8Bit(file.readAll());
  }

  file.close();
  return result;
}

QByteArray QFileUtils::loadFile(QString filepath)
{
  QByteArray result;
  QFile file(filepath);
  if (!file.exists()){
    qWarning() << "File" << file.fileName() << "doesn't exists";
    return result;
  }
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Cannot open file" << file.fileName();
    return result;
  }
  result = file.readAll();
  file.close();
  return result;
}

bool QFileUtils::stringToFile(QString str, QString filepath, bool isUtf)
{
  QFile file(filepath);
  bool result = file.open(QIODevice::WriteOnly);
  if (result){
    if (isUtf){
      file.write(str.toUtf8());
    } else {
      file.write(str.toLocal8Bit());
    }
    file.close();
  }
  return result;
}

QString QFileUtils::transliterate(QString &inStr)
{
    QString result = inStr;
    result = result.replace("А","A", Qt::CaseInsensitive);
    result = result.replace("Б","B", Qt::CaseInsensitive);
    result = result.replace("В","V", Qt::CaseInsensitive);
    result = result.replace("Г","G", Qt::CaseInsensitive);
    result = result.replace("Д","D", Qt::CaseInsensitive);
    result = result.replace("Е","E", Qt::CaseInsensitive);
    result = result.replace("Ж","ZH", Qt::CaseInsensitive);
    result = result.replace("З","Z", Qt::CaseInsensitive);
    result = result.replace("И","I", Qt::CaseInsensitive);
    result = result.replace("К","K", Qt::CaseInsensitive);
    result = result.replace("Л","L", Qt::CaseInsensitive);
    result = result.replace("М","M", Qt::CaseInsensitive);
    result = result.replace("Н","N", Qt::CaseInsensitive);
    result = result.replace("О","O", Qt::CaseInsensitive);
    result = result.replace("П","P", Qt::CaseInsensitive);
    result = result.replace("Р","R", Qt::CaseInsensitive);
    result = result.replace("С","S", Qt::CaseInsensitive);
    result = result.replace("Т","T", Qt::CaseInsensitive);
    result = result.replace("У","U", Qt::CaseInsensitive);
    result = result.replace("Ф","F", Qt::CaseInsensitive);
    result = result.replace("Х","H", Qt::CaseInsensitive);
    result = result.replace("Ц","C", Qt::CaseInsensitive);
    result = result.replace("Ш","SH", Qt::CaseInsensitive);
    result = result.replace("Щ","SH", Qt::CaseInsensitive);
    result = result.replace("Ь","", Qt::CaseInsensitive);
    result = result.replace("Ъ","", Qt::CaseInsensitive);
    result = result.replace("Э","E", Qt::CaseInsensitive);
    result = result.replace("Ю","YU", Qt::CaseInsensitive);
    result = result.replace("Я","YA", Qt::CaseInsensitive);
    result = result.replace(" ", "_");
    return result;
}

bool QFileUtils::forcePath(const QString &path)
{
  QDir dir;
  return dir.mkpath(path);
}

QString QFileUtils::extractDirPath(const QString &fullPath)
{
  QFileInfo info(fullPath);
  return info.absolutePath();
}

QString QFileUtils::extractFileName(const QString &fullPath)
{
  QFileInfo info(fullPath);
  return info.fileName();
}

QString QFileUtils::mimeFromExtension(QString filename)
{
  QString ext = filename.section(".", -1, -1);
  if (ext == "txt") {
    return "text/plain";
  }
  else if (ext == "aif") {
    return "audio/aiff";
  }
  else if (ext == "avi") {
    return "video/avi";
  }
  else if (ext == "bmp") {
    return "image/bmp";
  }
  else if (ext == "conf") {
    return "text/plain";
  }
  else if (ext == "cpp") {
    return "text/plain";
  }
  else if (ext == "css") {
    return "text/css";
  }
  else if (ext == "exe") {
    return "application/octet-stream";
  }
  else if (ext == "gif") {
    return "image/gif";
  }
  else if (ext == "h") {
    return "text/plain";
  }
  else if (ext == "htm") {
    return "text/html";
  }
  else if (ext == "html") {
    return "text/html";
  }
  else if (ext == "ico") {
    return "image/x-icon";
  }
  else if (ext == "java") {
    return "text/plain";
  }
  else if (ext == "jpeg") {
    return "image/jpeg";
  }
  else if (ext == "jpg") {
    return "image/jpeg";
  }
  else if (ext == "js") {
    return "text/javascript";
  }
  else if (ext == "lst") {
    return "text/plain";
  }
  else if (ext == "mov") {
    return "video/quicktime";
  }
  else if (ext == "mp3") {
    return "audio/mpeg3";
  }
  else if (ext == "mp4") {
    return "video/mp4";
  }
  else if (ext == "mpeg") {
    return "video/mpeg";
  }
  else if (ext == "pct") {
    return "image/x-pict";
  }
  else if (ext == "pcx") {
    return "image/x-pcx";
  }
  else if (ext == "pdf") {
    return "application/pdf";
  }
  else if (ext == "pic") {
    return "image/pict";
  }
  else if (ext == "png") {
    return "image/png";
  }
  else if (ext == "pps") {
    return "application/mspowerpoint";
  }
  else if (ext == "ppt") {
    return "application/mspowerpoint";
  }
  else if (ext == "psd") {
    return "application/octet-stream";
  }
  else if (ext == "py") {
    return "text/x-script.phyton";
  }
  else if (ext == "pyc") {
    return "applicaiton/x-bytecode.python";
  }
  else if (ext == "rtf") {
    return "text/richtext";
  }
  else if (ext == "sh") {
    return "application/x-bsh";
  }
  else if (ext == "tar") {
    return "application/x-tar";
  }
  else if (ext == "text") {
    return "text/plain";
  }
  else if (ext == "tgz") {
    return "application/x-compressed";
  }
  else if (ext == "tif") {
    return "image/tiff";
  }
  else if (ext == "wav") {
    return "audio/wav";
  }
  else if (ext == "wmf") {
    return "windows/metafile";
  }
  else if (ext == "xls") {
    return "application/excel";
  }
  else if (ext == "xml") {
    return "text/xml";
  }
  else if (ext == "z") {
    return "application/x-compress";
  }
  else if (ext == "zip") {
    return "application/zip";
  }
  else {
    return "text/plain";
  }
}

bool QFileUtils::saveFile(const QString &filepath, const QByteArray &data)
{
  QFile file(filepath);
  if (!file.open(QFile::WriteOnly))
    return false;
  file.write(data);
  return true;
}

bool QFileUtils::copyDirectory(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
  qDebug() << "Copying directory:" << fromDir << "->" << toDir;

  QDir sourceDir(fromDir);
  QDir targetDir(toDir);
  if(!targetDir.exists()){    /* if directory don't exists, build it */
    if(!targetDir.mkdir(targetDir.absolutePath()))
      return false;
  }

  QFileInfoList fileInfoList = sourceDir.entryInfoList();
  foreach(QFileInfo fileInfo, fileInfoList){
    if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
      continue;

    if(fileInfo.isDir()){    /* if it is directory, copy recursively*/
      if(!copyDirectory(fileInfo.filePath(),
                             targetDir.filePath(fileInfo.fileName()),
                             coverFileIfExist))
        return false;
    }
    else {            /* if coverFileIfExist == true, remove old file first */
      if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
        targetDir.remove(fileInfo.fileName());
      }

      // files copy
      if(!QFile::copy(fileInfo.filePath(),
                      targetDir.filePath(fileInfo.fileName()))){
        return false;
      }
    }
  }
  return true;
}

QStringList QFileUtils::filesOfDir(const QString &folderPath)
{
    QDir dir(folderPath);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    return dir.entryList();
}

QFilePath::QFilePath(QString fullpath)
{
  _fullPath = fullpath;
  _extension = QFilePath::extension(fullpath);
  _filename = QFilePath::filename(fullpath);
  _folderPath = QFilePath::folderPath(fullpath);
}

QString QFilePath::extension()
{
  return _extension;
}

QString QFilePath::folderPath()
{
  return _folderPath;
}

QString QFilePath::filename()
{
  return _filename;
}

bool QFilePath::isFolder()
{
  return !_filename.isEmpty();
}

QString QFilePath::extension(const QString &path)
{
  return QFilePath::isFolder(path) ? "" : path.section(".", -1, -1);
}

QString QFilePath::folderPath(const QString &path)
{
  return QFilePath::isFolder(path) ? path : path.section("/", 0, -2);
}

QString QFilePath::filename(const QString &path)
{
  return QFilePath::isFolder(path) ? "" : path.section("/", -1, -1);
}

bool QFilePath::isFolder(const QString &path)
{
  return !path.contains('.');
}
