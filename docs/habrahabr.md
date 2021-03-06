Существует множество библиотек графического интерфейса для микроконтроллеров и встраиваемых систем, но многие из них имеют ограниченный функционал, сложность в использовании и интеграции, необходимость обязательного использования внешней оперативной памяти, а некоторые стоят больше, чем ваш проект целиком. Из-за этих причин и многих других было решено писать свою библиотеку.

Назвал я её [MakiseGui](https://github.com/SL-RU/MakiseGUI).
 <habracut/>

Перед началом разработки я поставил себе цели:
* Простота конечной разработки. Писать интерфейс не должно быть сложнее, чем используя WindowsForms и тп
* Простота интеграции. Встроить и запустить интерфейс в приложении должно быть максимально просто на любом железе или ПО.
* Чистый Си. Был использован только gnu-c99 и из библиотек только stdlib
* Минимальное потребление RAM. Возможность использования на средних микроконтроллерах без внешней памяти(примерно 40kb с цветным дисплеем 320х240).
* Достаточное количество графических элементов для комфортной разработки. Простое добавление новых.
* opensource лицензия и бесплатное использование даже в коммерческих проектах


# Пример без объяснений.

В качестве демонстрации возможностей библиотеки и примеров использования может быть использован проект созданный специально для этих целей: https://github.com/SL-RU/MakiseSDLTest 

Он использует SDL2 для отрисовки и ввода и имеет примеры использования всех элементов и почти всех функций системы. Может быть скомпиллирован и запущен на любом linux дистрибутиве. На windows тоже, но лишь теоретически - сам не пробовал.

Видео работы:


# Структура

Библиотека состоит из трёх чётко разделённых частей: 

1) Ядро. Ядро состоит из интерфейса к драйверу, функций отрисовки в драйвер и функций отрисовки примитивов в буфер.
2) Драйвер. Драйвер обеспечивает всё общение с железом и с ПО, поэтому под каждую задачу придётся писать обычно свой, чтобы учесть все моменты(DMA, прерывания и тд). Драйвер лишь обеспечивает передачу изображения из буфера на железо и очищает буфер изображения. Как примеры, в проекте есть драйверы для дисплея на ili9340, а так же SDL2 для отладки библиотеки на компьютере. Ядро и драйвер могут работать отдельно, без GUI.
3) Сам GUI. Занимает бОльшую часть системы, тут воплощены все необходимые функции для работы интерфейса: контейнеры, элементы, системы отрисовки, фокуса, ввода, обработки событий и прочего.

# GUI

Разработка графического интерфейса максимально приближена к объектно-ориентированному для максимальной простоты конечного программирования. Благодаря этому она имеет некоторые приятные особенности

Простейший пример, создающий кнопку на экране:
```C
MHost host; //базовая структура системы, root-контейнер, содержащий все другие контейнеры и элементы.

//метод будет вызыван при нажатии на кнопку
void click(MButton *b)
{
	printf("Button was clicked"); //выводим сообщение в стандартный поток
	b->text = "Clicked!"; //меняем текст кнопки
	
}
MButton button; //структура, содержащая всю информацию о кнопке
void create_gui()
{
	//создаём кнопку
	m_create_button(&button, //указатель на структуру кнопки
		host->host, //контейнер, в который будет добавлена кнопка после создания. В данном случае это контейнер MHost'a
		mp_rel(20, 20, //координаты элемента относительно левого верхнего угла
		       90, 30), //ширина, высота
		"Click me",   //текст кнопки
		//События
		&click, //Вызывается при нажатии на кнопку
		0, //Вызывается до обработки нажатия, может прервать обработку нажатия
		0, //Вызывается при действиях с фокусом кнопки
		&ts_button //стиль кнопки
	);
}

void main()
{
	//тут была инициализация MakiseGui, драйвера, MakiseBuffer и MHost. Запуск драйвера.
	create_gui();
	while(1)
	{
		//драйвер вызывает функции рисовки
		//совершается ввод
		//и логика
	}
}

```

Итого, этот пример создаёт на экране кнопку при нажатии на которую в стандартном потоке вывода появится надпись "Button was clicked" и текст кнопки изменится.


## Инициализация

Инициализация предполагает только лишь запуск драйвера, задание размеров и выделение памяти для структур и буфферов элементов. Чисто формальная операция. Как инициализировать систему можно поглядеть тут: https://github.com/SL-RU/MakiseSDLTest/blob/master/src/main.c в методе start\_m();

## Ввод

Ввод приспособлен для работы в мультипоточных приложениях - он имеет очередь событий, которые посылаются интерфейсу при вызове makise\_gui\_input_perform(host);

Любое событие ввода представлено структурой MInputData. 

Возможен ввод кнопок(список стандартных в makise\_gui\_input.h MInputKeyEnum), символов(пока нигде не используется) и ввод курсора(сенсорный экран или мышь). В примере с SDL используется ввод с клавиатуры и ввод мышью.

## Контейнеры.

MContainer - структура контейнера. 

Контейнеры содержат связанный список элементов. Из контейнеров можно удалять или добавлять элементы, перемещать их и совершать другие операции. 

Позиция элемента в контейнере прямо влияет на очередь отрисовки и ввода.

Линкованый список осуществляется при помощи указателей на первый и последний элемент списка MElement и в структуре MElement имеются указатели на следующий и предыдущий элемент.

## Элементы.

Любой элемент представлен ввиде структуры MElement, которая содержит в себе информацию о элементе, указатели на функции отрисовки, ввода, фокуса и тд элемента и указатель на его содержимое.

На данный момент существуют следующие элементы:

* MButton - кнопка. Которая отображает текст посылает события при нажатии
* MCanvas - простейший контейнер, который просто содержит элементы.
* MLable - простейшее текстовое поле
* MTextField - текстовое поле, поддерживающее перенос слов и переносы
* MSlider - слайдер
* MToggle - кнопка имеющая два состояния.
* MSlist - список. Может быть как просто списком, так и radioкнопками, так и чекбосками. Поддерживает обычные списки и динамические линкованные.
* MTabs - вкладки. Несколько переключаемых контейнеров.

Лучшей документацией являются примеры, поэтому для каждого элемента есть свои примеры использования. Как сложные, так и простые.

## Стили

Стиль элемента определяет его внешний вид. Cтиль задаёт цвета элемента в определённом состоянии. За это отвечают структуры MakiseStyle и MakiseStyleTheme. MakiseStyle содержит несколько MakiseStyleTheme для определённых состояний, а так же параметры шрифта.

Для кнопки стиль может выглядеть так:

```C
MakiseStyle ts_button =
{
    MC_White,  //основной цвет. Не несёт никакого значения
    &F_Arial24,//Шрифт стиля
    0, //межстрочное расстояние
    //цвет заднего фона | шрифта   бортик    есть лидвойной бортик
    {MC_Black,           MC_Gray,  MC_Gray,  0     }, //когда кнопка не активна
    {MC_Black,           MC_White, MC_White, 0     }, //нормальное состояние
	{MC_White,           MC_Green, MC_White, 0     }, //в фокусе
	{MC_Green,           MC_White, MC_White, 0     }, //когда была кликнута
```

## Фокус

Фокус определяет к какому элементу пойдёт ввод. Для управления фокусом существуют следующие функции:

```C
MFocusEnum makise_g_focus(MElement *el, MFocusEnum event); //фокусирует или расфокусирует нужный элемент
MFocusEnum makise_g_host_focus_next(MHost *host);//переведёт фокус на следующий по очереди элемент
MFocusEnum makise_g_host_focus_prev(MHost *host);//на предыдущий
```

Немножко документации есть в репозитории. Но вся основная документация находиться в комментариях к функциям и в примерах. Задавайте вопросы! На основе них я буду дописывать документацию. 

Есть много моментов которые нужно совершенствовать в библиотеки и есть много путей развитя. Но на данный момент библиотека является совершенно рабочей и стабильной.

Лицензия проекта - MIT. Вы можете использовать библиотеку и исходный код как хотите и где хотите, но в то же время я не даю никаких гарантий по работе библиотеки - всё как есть.

Буду рад вопросам, пожеланиям и пулл реквестам!
