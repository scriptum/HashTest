#include <QHash>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "perf_timer.h"

#ifndef TABLE_SIZE
#define TABLE_SIZE words.size()
#endif

int main()
{
	QVector<QString> words;
	QFile inputFile("dictionary.txt");
	if(inputFile.open(QIODevice::ReadOnly))
	{
		QTextStream in(&inputFile);
		while(!in.atEnd())
			words.append(in.readLine().trimmed());
	}
	inputFile.close();
	
	QString s;
	QHash<QString, int> hashtable;
	perf_timer_start();
	for(int i = 0; i < 20000000; i++)
		hashtable[words[i % TABLE_SIZE]]++;
	perf_timer_end();
	perf_timer_print();
	return 0;
}
