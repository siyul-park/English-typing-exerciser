﻿/**
* include
*/

#include "Platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if (_PLATFORM_TYPE == _PLATFORM_WIN32)
#include <conio.h>
#elif (_PLATFORM_TYPE == _PLATFORM_LINUX || _PLATFORM_TYPE == _PLATFORM_UNIX)
#include <termio.h>
int _getche(void);
int _getch(void);
#endif

/**
* define
*/

#define TYPE_MENU 0
#define TYPE_SEATPRACTICE 1
#define TYPE_WORDPRACTICE 2
#define TYPE_SHORTSENTENCEPRACTICE 3
#define TYPE_LONGSENTENCEPRACTICE 4

#define RESOURCE_SIZE_SEATPRACTICE 52
#define RESOURCE_SIZE_WORDPRACTICE 100
#define RESOURCE_SIZE_LONGSENTENCEPRACTICE 4

#define INPUT_MAX 1000

/**
* 함수 prototypes
*/

int run(void);

int check_keyboard(void);

int screen_clear(void);
int screen_change(int _type);
int screen_draw(void);

int input_keyboard(char _input);
int input_keyboard_enter(void);
int input_keyboard_backspace(void);

int menu_draw(void);
int seat_practice_draw(void);
int word_practice_draw(void);
int short_sentence_practice_draw(void);
int long_sentence_practice_draw(void);

int menu_input_keyboard(char _input);
int seat_practice_input_keyboard(char _input);
int word_practice_input_keyboard(char _input);
int short_sentence_practice_input_keyboard(char _input);
int long_sentence_practice_input_keyboard(char _input);

int menu_input_keyboard_enter(void);
int seat_practice_input_keyboard_enter(void);
int word_practice_input_keyboard_enter(void);
int short_sentence_practice_input_keyboard_enter(void);
int long_sentence_practice_input_keyboard_enter(void);

int menu_input_keyboard_backspace(void);
int seat_practice_input_keyboard_backspace(void);
int word_practice_input_keyboard_backspace(void);
int short_sentence_practice_input_keyboard_backspace(void);
int long_sentence_practice_input_keyboard_backspace(void);

char* get_resource(void);

/**
* 외부 변수 선언
*/

int is_running = 0;

int progress = 0;
int num_of_typo = 0;
int accuracy = 0;

int current_typing_count = 0;
int highest_typing_count = 0;

// 현재까지 입력한 개수
int typing_count = 0;

// 시간
clock_t start_clock = 0;
clock_t finsh_clock = 0;

int window_type = 0;

// 출력할 값
char* output_buffer = 0;
// 입력된 값 임지 저장
char* tmp_output_buffer = 0;
// 입력된 값
char input_buffer[INPUT_MAX] = { 0 };
// 입력된 값 임지 저장
char tmp_input_buffer[INPUT_MAX] = { 0 };
// 입력된 값의 수
int input_num = 0;
// 입력될수 있는 문자의 수
int input_max = 0;;

char* resorce_seat_practice[RESOURCE_SIZE_SEATPRACTICE] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
char* resorce_word_practice[RESOURCE_SIZE_WORDPRACTICE] = { "accident", "advice", "already", "assistant", "bake", "bathtub", "bit", "border", "breathe", "brick", "bud", "cafe", "capital", "chance", "cheat", "clear", "control", "couple", "court", "crowd", "culture", "dangerous", "date", "diary", "diet", "director", "discover", "document", "doubt", "during", "earth", "edge", "emperor", "ever", "expect", "experiment", "explain", "fair", "famous", "favor", "few", "fight", "final", "gate", "gentle", "golden", "greedy", "guest", "heat", "history", "hit", "horror", "host", "hunt", "hurry", "ingredient", "invent", "judge", "junk", "koala", "korea", "kid", "language", "leave", "lend", "lie", "lose", "marry", "mask", "member", "mind", "mix", "modern", "oil", "ocean", "pan", "peck", "perfect", "piece", "pour", "proud", "quiz", "quiet", "race", "recipe", "report", "review", "roll", "root", "rule", "secret", "smart", "swan", "title", "uniform", "volunteer", "wet", "whale", "wonder" };
char* resorce_long_sentence_practice[RESOURCE_SIZE_LONGSENTENCEPRACTICE] = { "I read the review of Social Distortion by Jack Churchill and couldn't have been more let down.\nIt felt like a book report written by a child.\n Churchill made no attempt to describe parts of the set list, or the highs and lows of the show, but instead wrote.\nHe ignored the parts of the show where Mike Ness stopped to talk about the inspiration for some of his songs and opened up to the audience.\n The only reason I can think of that tou would even print this uninspired review is to use the photos that were taken at the show." , "Teachers who are new to the integration of\nsocial media into their teaching practice often\nmake the mistake of focusing on a particular tool\nthey want to use with their class instead of on\nthe purposes or intended outcomes of a teaching\nand learning episode. For example, a teacher\nmay become attracted to blogs and decide to use\nblogs for anything and everything, regardless of\nthe suitability of the blogging format for what\nthe teacher wants students to achieve.\n" , "If your child is able to be responsible for his\ntoys, tou can slowly add to their responsibilities\nby getting them to care for themselves in various\nways such as getting dressed, brushing their teeth\non their own, and being responsible for their home\nenvironment such as cleaning up their dishes after\ntheir meals or making their dishes after\ntheir meals making their bed. However, it is\nimportant that you show them how to do it by\nbreaking it down into small manageable steps and\n", "A biography tells an account of a person life\nwritten in the third person in a narrative structure.\nBiographies can be studied to learn about how\npeople reacted to, shaped, and constructed\nopportunities during historical periods and the\ncultural contexts in which they lived. They\nprovide nonfiction information and communicate\nwhy a person's legacy is so important that it\ndocumented. Reading biographies can help\nstudents reflect about how they should feel about\n" };

/**
* 함수 정의
*/

/**
* main: 메인 루프를 활성화해주고, 난수를 초기화하고, run함수를 호출합니다.
*/
int main(void)
{
    is_running = 1;

    srand(time(NULL));
    run();

    return 0;
}

/**
* run: screen_clear, screen_draw, check_keyboard을 호출하는 메인 루프를 실행합니다.
*/
int run(void)
{
    input_max = 1;

    while (is_running)
    {
        screen_clear();
        screen_draw();
        check_keyboard();
    }

    return 0;
}

/**
* check_keyboard: 키보드 입력을 받아 입력 값에 따라 다른 함수를 호출 해주고, 특수 문자가 아닌 경우 input_buffer에 넣어줍니다.
*/
int check_keyboard(void)
{
    char ch;

    if (input_max > input_num)
        ch = _getche();
    else
        ch = _getch();
    finsh_clock = clock();
    if (ch == '\x1B')
    {
        if (window_type)
            screen_change(TYPE_MENU);
    }
    else if (ch == '\x7F' || ch == '\x8')
    {
        input_keyboard_backspace();

        if (input_num > 0)
        {
            input_num--;
            input_buffer[input_num] = 0;
        }
    }
    else if (ch == '\x0D' || ch == '\x0A')
    {
        input_keyboard_enter();
    }
    else
    {
        if (input_max > input_num)
        {
            input_buffer[input_num] = ch;
            input_num++;
        }

        input_keyboard(ch);
    }

    return 0;
}

/**
* screen_clear: 화면을 지워 줍니다.
*/
int screen_clear(void)
{
    printf("\n");

#if (_PLATFORM_TYPE == _PLATFORM_WIN32)
    return system("CLS");
#elif (_PLATFORM_TYPE == _PLATFORM_LINUX || _PLATFORM_TYPE == _PLATFORM_UNIX)
    return system("clear");
#endif
}

/**
* screen_change: _type의 값으로 화면을 바꿔 줍니다.
*/
int screen_change(int _type)
{

    if (_type == 5)
    {
        is_running = 0;

        return _type;
    }

    window_type = _type;

    progress = 0;
    num_of_typo = 0;
    accuracy = 0;

    current_typing_count = 0;
    highest_typing_count = 0;

    typing_count = 0;

    start_clock = clock();
    finsh_clock = 0;

    output_buffer = get_resource();
    tmp_output_buffer = 0;

    for (; input_num > 0; --input_num)
        input_buffer[input_num - 1] = 0;

    for (int i = 0; i < INPUT_MAX; ++i)
        tmp_input_buffer[i] = 0;

    switch (window_type)
    {
    case TYPE_MENU:
        input_max = 1;
        break;
    case TYPE_SEATPRACTICE:
        input_max = strlen(output_buffer);
        break;
    case TYPE_WORDPRACTICE:
        input_max = strlen(output_buffer);
        break;
    case TYPE_SHORTSENTENCEPRACTICE:

        break;
    case TYPE_LONGSENTENCEPRACTICE:
        input_max = strlen(output_buffer);
        break;
    default:
        break;
    }


    return _type;
}

/**
* screen_draw: 화면을 window_type에 따라 그려주기 위해 각각 다른 함수를 호출해줍니다.
*/
int screen_draw(void)
{
    switch (window_type)
    {
    case TYPE_MENU:
        menu_draw();
        break;
    case TYPE_SEATPRACTICE:
        seat_practice_draw();
        break;
    case TYPE_WORDPRACTICE:
        word_practice_draw();
        break;
    case TYPE_SHORTSENTENCEPRACTICE:
        short_sentence_practice_draw();
        break;
    case TYPE_LONGSENTENCEPRACTICE:
        long_sentence_practice_draw();
        break;
    default:
        break;
    }

    return 0;
}

/**
* input_keyboard: 키보드에 특수 문자가 아닌 다른 값이 입력 되었을 때 호출됩니다. 현재 입력된 값인 _input을 window_type에 각각 다른 함수에 넘겨줍니다.
*/
int input_keyboard(char _input)
{
    switch (window_type)
    {
    case TYPE_MENU:
        menu_input_keyboard(_input);
        break;
    case TYPE_SEATPRACTICE:
        seat_practice_input_keyboard(_input);
        break;
    case TYPE_WORDPRACTICE:
        word_practice_input_keyboard(_input);
        break;
    case TYPE_SHORTSENTENCEPRACTICE:
        short_sentence_practice_input_keyboard(_input);
        break;
    case TYPE_LONGSENTENCEPRACTICE:
        long_sentence_practice_input_keyboard(_input);
        break;
    default:
        break;
    }

    return 0;
}

/**
* input_keyboard_enter: 키보드에 Enter키 또는 줄바꿈 문자가 입력 되었을 때 호출됩니다. window_type에 각각 다른 함수을 호출해줍니다.
*/
int input_keyboard_enter(void)
{
    switch (window_type)
    {
    case TYPE_MENU:
        menu_input_keyboard_enter();
        break;
    case TYPE_SEATPRACTICE:
        seat_practice_input_keyboard_enter();
        break;
    case TYPE_WORDPRACTICE:
        word_practice_input_keyboard_enter();
        break;
    case TYPE_SHORTSENTENCEPRACTICE:
        short_sentence_practice_input_keyboard_enter();
        break;
    case TYPE_LONGSENTENCEPRACTICE:
        long_sentence_practice_input_keyboard_enter();
        break;
    default:
        break;
    }

    return 0;
}

/**
* input_keyboard_backspace: 키보드에 backspace키 또는 delete가 입력 되었을 때 호출됩니다. window_type에 각각 다른 함수을 호출해줍니다.
*/
int input_keyboard_backspace(void)
{
    switch (window_type)
    {
    case TYPE_MENU:
        menu_input_keyboard_backspace();
        break;
    case TYPE_SEATPRACTICE:
        seat_practice_input_keyboard_backspace();
        break;
    case TYPE_WORDPRACTICE:
        word_practice_input_keyboard_backspace();
        break;
    case TYPE_SHORTSENTENCEPRACTICE:
        short_sentence_practice_input_keyboard_backspace();
        break;
    case TYPE_LONGSENTENCEPRACTICE:
        long_sentence_practice_input_keyboard_backspace();
        break;
    default:
        break;
    }

    return 0;
}

/**
* menu_input_keyboard: 키보드에 특수 문자가 아닌 다른 값이 입력 되었을 때 호출됩니다. 입력된 값이 _input에 넘겨집니다.
*/
int menu_input_keyboard(char _input)
{
    return 0;
}

/**
* seat_practice_input_keyboard: 키보드에 특수 문자가 아닌 다른 값이 입력 되었을 때 호출됩니다. 입력된 값이 _input에 넘겨집니다.
*/
int seat_practice_input_keyboard(char _input)
{
    if (progress < 100 && output_buffer)
    {
        if (output_buffer[input_num - 1] == _input)
        {
            progress += 5;

            output_buffer = get_resource();
            for (; input_num > 0; --input_num)
                input_buffer[input_num - 1] = 0;
        }
        else
            num_of_typo += 1;

        typing_count++;
        accuracy = 100 - num_of_typo * 100 / typing_count;
    }

    if (progress == 100)
        output_buffer = 0;

    return 0;
}

/**
* word_practice_input_keyboard: 키보드에 특수 문자가 아닌 다른 값이 입력 되었을 때 호출됩니다. 입력된 값이 _input에 넘겨집니다.
*/
int word_practice_input_keyboard(char _input)
{
    return 0;
}

/**
* short_sentence_practice_input_keyboard: 키보드에 특수 문자가 아닌 다른 값이 입력 되었을 때 호출됩니다. 입력된 값이 _input에 넘겨집니다.
*/
int short_sentence_practice_input_keyboard(char _input)
{
    return 0;
}

/**
* long_sentence_practice_input_keyboard: 키보드에 특수 문자가 아닌 다른 값이 입력 되었을 때 호출됩니다. 입력된 값이 _input에 넘겨집니다.
*/
int long_sentence_practice_input_keyboard(char _input)
{
    float diff_time;

    if (input_num == 0)
        start_clock = clock();

    finsh_clock = clock();
    diff_time = (float)(finsh_clock - start_clock) / CLOCKS_PER_SEC;

    if (output_buffer && output_buffer[input_num - 1] == _input)
        ++typing_count;
    else if (output_buffer)
        ++num_of_typo;

    current_typing_count = (typing_count / diff_time) * 60;
    accuracy = 100 - num_of_typo * 100 / (typing_count + num_of_typo);

    if (input_num == input_max && progress == 0)
    {
        tmp_output_buffer = output_buffer;
        output_buffer = get_resource();
        input_max = strlen(output_buffer);
        
        strcpy(tmp_input_buffer, input_buffer);

        for (; input_num > 0; --input_num)
            input_buffer[input_num - 1] = 0;

        progress = 100;

    }
    else if (input_num == input_max && progress == 100)
    {
        output_buffer = 0;

        for (; input_num > 0; --input_num)
            input_buffer[input_num - 1] = 0;
    }

    return 0;
}

/**
* menu_input_keyboard_enter: 키보드에 Enter키 또는 줄바꿈 문자가 입력 되었을 때 호출됩니다.
*/
int menu_input_keyboard_enter(void)
{
    if (input_num > 0 && input_buffer[input_num - 1])
        screen_change(input_buffer[input_num - 1] - '0');

    return 0;
}

/**
* menu_input_keyboard_enter: 키보드에 Enter키 또는 줄바꿈 문자가 입력 되었을 때 호출됩니다.
*/
int seat_practice_input_keyboard_enter(void)
{
    if (progress == 100)
        screen_change(TYPE_MENU);

    return 0;
}

/**
* word_practice_input_keyboard_enter: 키보드에 Enter키 또는 줄바꿈 문자가 입력 되었을 때 호출됩니다.
*/
int word_practice_input_keyboard_enter(void)
{
    if (!strncmp(input_buffer, "###", 3))
    {
        screen_change(TYPE_MENU);
        return 0;
    }
    else if (progress < 100 && output_buffer)
    {
        if (strcmp(input_buffer, output_buffer))
            num_of_typo += 1;

        progress += 5;

        if (progress != 100)
        {
            output_buffer = get_resource();
            input_max = strlen(output_buffer);
        }
        else
            output_buffer = 0;
        for (; input_num > 0; --input_num)
            input_buffer[input_num - 1] = 0;

        typing_count++;
        accuracy = 100 - num_of_typo * 100 / typing_count;
    }
    else if (progress == 100)
        screen_change(TYPE_MENU);

    return 0;
}

/**
* short_sentence_practice_input_keyboard_enter: 키보드에 Enter키 또는 줄바꿈 문자가 입력 되었을 때 호출됩니다.
*/
int short_sentence_practice_input_keyboard_enter(void)
{
    return 0;
}

/**
* long_sentence_practice_input_keyboard_enter: 키보드에 Enter키 또는 줄바꿈 문자가 입력 되었을 때 호출됩니다.
*/
int long_sentence_practice_input_keyboard_enter(void)
{
    if (progress == 100)
        screen_change(TYPE_MENU);

    return 0;
}

/**
* menu_input_keyboard_backspace: 키보드에 backspace키 또는 delete가 입력 되었을 때 호출됩니다.
*/
int menu_input_keyboard_backspace(void)
{
    return 0;
}

/**
* seat_practice_input_keyboard_backspace: 키보드에 backspace키 또는 delete가 입력 되었을 때 호출됩니다.
*/
int seat_practice_input_keyboard_backspace(void)
{
    return 0;
}

/**
* word_practice_input_keyboard_backspace: 키보드에 backspace키 또는 delete가 입력 되었을 때 호출됩니다.
*/
int word_practice_input_keyboard_backspace(void)
{
    return 0;
}

/**
* short_sentence_practice_input_keyboard_backspace: 키보드에 backspace키 또는 delete가 입력 되었을 때 호출됩니다.
*/
int short_sentence_practice_input_keyboard_backspace(void)
{
    return 0;
}

/**
* long_sentence_practice_input_keyboard_backspace: 키보드에 backspace키 또는 delete가 입력 되었을 때 호출됩니다.
*/
int long_sentence_practice_input_keyboard_backspace(void)
{
    if (progress == 0 && input_num == 0)
        return;
    
    if (input_num > 0)
    {
        float diff_time;

        finsh_clock = clock();
        diff_time = (float)(finsh_clock - start_clock) / CLOCKS_PER_SEC;

        if (output_buffer && output_buffer[input_num - 1] == input_buffer[input_num - 1])
            --typing_count;
        else if (output_buffer)
            --num_of_typo;

        current_typing_count = (typing_count / diff_time) * 60;
        if (typing_count + num_of_typo)
            accuracy = 100 - num_of_typo * 100 / (typing_count + num_of_typo);
        else
            accuracy = 0;
    }

    if (progress == 100 && input_num == 0)
    {
        output_buffer = tmp_output_buffer;
        input_max = strlen(output_buffer);

        strcpy(input_buffer, tmp_input_buffer);
        input_num = strlen(input_buffer);

        progress = 0;

    }


    return 0;
}


/**
* menu_draw: menu 화면을 그려줍니다.
*/
int menu_draw(void)
{
    printf(">> 영문 타자 연습 프로그램 <<\n");
    printf("1. 자리 연습         2. 낱말 연습\n");
    printf("3. 짧은 글 연습      4. 긴 글 연습 \n");
    printf("5. 프로그램 종료\n\n");
    printf("번호를 입력하세요: %s", input_buffer);

    return 0;
}

/**
* seat_practice_draw: seat_practice 화면을 그려줍니다.
*/
int seat_practice_draw(void)
{
    printf(">> 영문 타자 연습 프로그램 : 자리연습 <<\n");
    printf("진행도 : %d    오타수 : %d    정확도 : %d%%\n\n", progress, num_of_typo, accuracy);
    if (output_buffer)
        printf("%s\n", output_buffer);
    printf("%s", input_buffer);

    return 0;
}

/**
* word_practice_draw: word_practice 화면을 그려줍니다.
*/
int word_practice_draw(void)
{
    printf(">> 영문 타자 연습 프로그램 : 낱말 연습 <<\n");
    printf("진행도 : %d    오타수 : %d    정확도 : %d%%\n\n", progress, num_of_typo, accuracy);
    if (output_buffer)
        printf("%s\n", output_buffer);
    printf("%s", input_buffer);

    return 0;
}

/**
* short_sentence_practice_draw: short_sentence_practice 화면을 그려줍니다.
*/
int short_sentence_practice_draw(void)
{
    return 0;
}

/**
* long_sentence_practice_draw: long_sentence_practice 화면을 그려줍니다.
*/
int long_sentence_practice_draw(void)
{
    printf(">>영문 타자 연습 프로그램 : 긴 글 연습<<\n");
    printf("정확도 : %d%%    현재타수 : %d\n\n", accuracy, current_typing_count);
    if (output_buffer)
        printf("%s\n", output_buffer);
    printf("%s", input_buffer);

    return 0;
}

/**
* get_resource: window_type별로 다른 리소스를 찾아서 Return해 줍니다.
*/
char* get_resource(void)
{
    char* ch = 0;

    switch (window_type)
    {
    case TYPE_MENU:
        break;
    case TYPE_SEATPRACTICE:
        ch = resorce_seat_practice[rand() % RESOURCE_SIZE_SEATPRACTICE];
        break;
    case TYPE_WORDPRACTICE:
        ch = resorce_word_practice[rand() % RESOURCE_SIZE_WORDPRACTICE];
        break;
    case TYPE_SHORTSENTENCEPRACTICE:

        break;
    case TYPE_LONGSENTENCEPRACTICE:
        ch = resorce_long_sentence_practice[rand() % RESOURCE_SIZE_LONGSENTENCEPRACTICE];
        break;
    default:
        break;
    }

    return ch;
}

#if (_PLATFORM_TYPE == _PLATFORM_LINUX || _PLATFORM_TYPE == _PLATFORM_UNIX)
int _getche(void)
{
    int ch;

    struct termios _old;
    struct termios _new;

    tcgetattr(0, &_old);

    _new = _old;
    _new.c_lflag |= (ICANON | ECHO);
    _new.c_cc[VMIN] = 1;
    _new.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &_new);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &_old);

    return ch;
}
int _getch(void)
{
    int ch;

    struct termios _old;
    struct termios _new;

    tcgetattr(0, &_old);

    _new = _old;
    _new.c_lflag &= ~(ICANON | ECHO);
    _new.c_cc[VMIN] = 1;
    _new.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &_new);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &_old);

    return ch;
}
#endif