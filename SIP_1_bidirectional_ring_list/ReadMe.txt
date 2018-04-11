========================================================================
    CONSOLE APPLICATION : SIP_1_bidirectional_ring_list Project Overview
========================================================================

+	добавление элемента после последнего; 
+	добавление элемента перед первым; 
+	добавление элемента по порядку; то чего нет в списке. Только при добавлении нового эл-та. 
+	удаление элемента с указанной информационной частью;
+	поиск элемента;
+	удаление всех элементов; (пока есть только в деструкторе, но уже хоть что-то)
-+	сортировка элементов;
-	упорядочение текущего элемента (предполагается, что все остальные элементы упорядочены);
-	копирование структуры данных с помощью перегруженного оператора присваивания;
+	перегруженный оператор !, определяющий существование элементов в структуре данных.

+	поле (недоступное пользователю), хранящее указатель на текущий элемент;
-	получение ссылки на информационную часть текущего элемента (возвращает удачность операции);
-	получение копии информационной части текущего элемента (возвращает удачность операции);
+	перегруженный оператор ++ (префиксный) для перехода к следующему элементу;
+	перегруженный оператор -- (префиксный) для перехода к предыдущему элементу (для двунаправленного списка);
-	метод, переводящий указатель на текущий элемент в начало (конец, при необходимости) списка.




AppWizard has created this SIP_1_bidirectional_ring_list application for you.

This file contains a summary of what you will find in each of the files that
make up your SIP_1_bidirectional_ring_list application.


SIP_1_bidirectional_ring_list.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

SIP_1_bidirectional_ring_list.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

SIP_1_bidirectional_ring_list.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named SIP_1_bidirectional_ring_list.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
