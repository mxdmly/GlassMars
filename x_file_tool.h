#ifndef X_FILE_TOOL_H
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#define X_FILE_TOOL_H


class x_file_tool
{
public:
    x_file_tool();
    x_file_tool(QWidget *qwidge);
    ~x_file_tool();

    QString filePath_str;
};

#endif // X_FILE_TOOL_H
