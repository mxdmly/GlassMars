#include "x_file_tool.h"

x_file_tool::x_file_tool()
{
    //this
}

x_file_tool::x_file_tool(QWidget *qwidge)
{
    filePath_str = QFileDialog::getSaveFileName(qwidge, QObject::tr("Save as..."), QString(), QObject::tr("EXCEL files (*.xls *.xlsx);;HTML-Files (*.txt);;"));
}

x_file_tool::~x_file_tool(){

}
