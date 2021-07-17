     #include <stdio.h>  // Включаем заголовок для стандартного ввода-вывода
          
          // Главная функция программы-скрипта
          int main()
          {
             // Перед тем, как выводить сам HTML документ,
             // необходимо вывести информацию для браузера:
             printf("Content-type: text/html\n");  // тип посылаемых данных - HTML документ
             printf("Pragma: no-cache\n");         // запрещаем кэширование страницы
             printf("\n");                         // двойной перевод каретки - признак
                                                   // конца информации для браузера
             // Теперь можем смело выводить HTML документ
             printf("<html>\n");
             printf("  <body>\n");
             printf("    <h1 align=center>Hello, World!</h1>\n");
             printf("  </body>\n");
             printf("</html>\n");
			 printf("OKKkkk");

             return 0;       
          }