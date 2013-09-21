#ifndef PARSER_H
#define PARSER_H
#include "module.h"
#include <QRegExp>
class Parser
{
public:
    Parser(QString &FileName);
    void ParsingModules(QString& FileName);
    QVector<Module> ModulesIF;
private:

    QRegExp RegExp;

};

#endif // PARSER_H
