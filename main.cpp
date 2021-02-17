#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void enter_matrice_size(int &width_of_matrice,int &hight_of_matrice,int index_of_matrice)
{
    do
    {
        cout << "Введите размеры матрицы № "<< index_of_matrice << " (значение большьше 0)\n";
        cin >> width_of_matrice >> hight_of_matrice;
    } while (width_of_matrice <= 0 || hight_of_matrice <= 0);
}

void filling_of_matrices(int** first_matrice,int** second_matrice, int width_of_first_matrice, int hight_of_first_matrice,
                         int width_of_second_matrice, int hight_of_second_matrice)
{
    int matrice_filling_mode;
    do
    {
        cout << "Выберите способ заполнения матриц\n" <<
            "1 - Вручную \n2 - Случайным образом\n";
        cin >> matrice_filling_mode;
    } while (matrice_filling_mode != 1 && matrice_filling_mode != 2);

    if (matrice_filling_mode == 1)
    {
        for (int i = 0; i < width_of_first_matrice; i++)
            for (int j = 0; j < hight_of_first_matrice; j++)
                cin >> first_matrice[i][j];
        for (int i = 0; i < width_of_second_matrice; i++)
            for (int j = 0; j < hight_of_second_matrice; j++)
                cin >> second_matrice[i][j];
    }
    else
    {
        for (int i = 0; i < width_of_first_matrice; i++)
            for (int j = 0; j < hight_of_first_matrice; j++)
                first_matrice[i][j] = rand() % 10;
        for (int i = 0; i < width_of_second_matrice; i++)
            for (int j = 0; j < hight_of_second_matrice; j++)
                second_matrice[i][j] = rand() % 10;
    }
}

void output_matrice(int** matrice, int width_of_matrice, int hight_of_matrice)
{
    for (int i = 0; i < width_of_matrice; i++)
    {
        for (int j = 0; j < hight_of_matrice; j++)
            cout << matrice[i][j] << " ";
        cout << endl;
    }
}

void bringing_matrices(int** new_matrice, int** old_matrice,int size_of_new_matrice, int width_of_old_matrice, int hight_of_old_matrice)
{
    for (int i = 0; i < size_of_new_matrice; i++)
    {
        new_matrice[i] = new int[size_of_new_matrice];
        for (int j = 0; j < size_of_new_matrice; j++)
            new_matrice[i][j] = 0;
    }
    for (int i = 0; i < width_of_old_matrice; i++)
    {
        for (int j = 0; j < hight_of_old_matrice; j++)
            new_matrice[i][j] = old_matrice[i][j];
    }
}
void copying_values_to_matrice(int size_of_new_matrice, int** new_matrice, int** old_matrice,int shift_i, int shift_j)
{
    for (int i = 0; i < size_of_new_matrice; i++)
    {
        new_matrice[i] = new int[size_of_new_matrice];
        for (int j = 0; j < size_of_new_matrice; j++)
            new_matrice[i][j] = old_matrice[i+shift_i][j+ shift_j];
    }
}

void delete_matrice(int** matrice, int width_of_matrice)
{
    for (int i = 0; i < width_of_matrice; i++)
        delete[] matrice[i];
    delete[] matrice;
}

void aligning_the_bounds(int size_of_matrice, int &bound_1, int& bound_2, int** old_matrice)
{
    int timed_1 = 0;
    int timed_2 = 0;
    int max_bound_1 = bound_1;
    int max_bound_2 = bound_2;
    for (int i = 0; i < size_of_matrice; i++)
    {
        timed_1 = 0;
        timed_2 = 0;
        for (int j = 0; j < size_of_matrice; j++)
        {
            if (old_matrice[i][j] != 0)
            {
                timed_1++;
                bound_1 = max_bound_1;
            }

            if (old_matrice[j][i] != 0)
            {
                timed_2++;
                bound_2 = max_bound_2;
            }
        }
        if (timed_1 == 0 && i < bound_1)
        {
            bound_1 = i;
        }
        if (timed_2 == 0 && i < bound_2)
        {
            bound_2 = i;
        }
    }
}

void calculation_of_matrices()
{
    int width_of_first_matrice, hight_of_first_matrice,
        width_of_second_matrice, hight_of_second_matrice,
        size_of_intermediate_matrice = 2;


    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////Ввод размеров матрицы пользователем////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    enter_matrice_size(width_of_first_matrice, hight_of_first_matrice, 1);
    enter_matrice_size(width_of_second_matrice, hight_of_second_matrice, 1);

    int** first_matrice = new int* [width_of_first_matrice];
    int** second_matrice = new int* [width_of_second_matrice];
    for (int i = 0; i < width_of_first_matrice; i++)
        first_matrice[i] = new int[hight_of_first_matrice];

    for (int i = 0; i < width_of_second_matrice; i++)
        second_matrice[i] = new int[hight_of_second_matrice];

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////Выбор способа заполнения и заполнение матриц///////////////////
    ///////////////////////////////////////////////////////////////////////////////

    filling_of_matrices(first_matrice,second_matrice,width_of_first_matrice,
                        hight_of_first_matrice,width_of_second_matrice, hight_of_second_matrice);

    cout << "\nМатрица 1\n\n";
    output_matrice(first_matrice, width_of_first_matrice, hight_of_first_matrice);
    cout << "\nМатрица 2\n\n";
    output_matrice(second_matrice, width_of_second_matrice, hight_of_second_matrice);

    ///////////////////////////////////////////////////////////////////////////////
    /////////////////Приведение матриц к требуемому размеру////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    while (size_of_intermediate_matrice < width_of_first_matrice || size_of_intermediate_matrice < hight_of_first_matrice
        || size_of_intermediate_matrice < width_of_second_matrice || size_of_intermediate_matrice < hight_of_second_matrice)
        size_of_intermediate_matrice *= 2;
    int** therd_matrice = new int* [size_of_intermediate_matrice];
    bringing_matrices(therd_matrice, first_matrice, size_of_intermediate_matrice, width_of_first_matrice, hight_of_first_matrice);
    int** fouth_matrice = new int* [size_of_intermediate_matrice];
    bringing_matrices(fouth_matrice, second_matrice, size_of_intermediate_matrice, width_of_second_matrice, hight_of_second_matrice);

    cout << "Приведенные матрицы\n";
    cout << "\nМатрица 1\n\n";
    output_matrice(therd_matrice, size_of_intermediate_matrice, size_of_intermediate_matrice);
    cout << "\nМатрица 2\n\n";
    output_matrice(fouth_matrice, size_of_intermediate_matrice, size_of_intermediate_matrice);

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** podmatrice_1_of_therd = new int* [size_of_intermediate_matrice / 2];
    int** podmatrice_2_of_therd = new int* [size_of_intermediate_matrice / 2];
    int** podmatrice_3_of_therd = new int* [size_of_intermediate_matrice / 2];
    int** podmatrice_4_of_therd = new int* [size_of_intermediate_matrice / 2];
    copying_values_to_matrice(size_of_intermediate_matrice / 2, podmatrice_1_of_therd, therd_matrice, 0, 0);
    copying_values_to_matrice(size_of_intermediate_matrice / 2, podmatrice_2_of_therd, therd_matrice, 0, size_of_intermediate_matrice / 2);
    copying_values_to_matrice(size_of_intermediate_matrice / 2, podmatrice_3_of_therd, therd_matrice, size_of_intermediate_matrice / 2, 0);
    copying_values_to_matrice(size_of_intermediate_matrice / 2, podmatrice_4_of_therd, therd_matrice, size_of_intermediate_matrice / 2, size_of_intermediate_matrice / 2);

    int** podmatrice_1_of_fouth = new int* [size_of_intermediate_matrice / 2];
    int** podmatrice_2_of_fouth = new int* [size_of_intermediate_matrice / 2];
    int** podmatrice_3_of_fouth = new int* [size_of_intermediate_matrice / 2];
    int** podmatrice_4_of_fouth = new int* [size_of_intermediate_matrice / 2];
    copying_values_to_matrice(size_of_intermediate_matrice / 2, podmatrice_1_of_fouth, fouth_matrice, 0, 0);
    copying_values_to_matrice(size_of_intermediate_matrice / 2, podmatrice_2_of_fouth, fouth_matrice, 0, size_of_intermediate_matrice / 2);
    copying_values_to_matrice(size_of_intermediate_matrice / 2, podmatrice_3_of_fouth, fouth_matrice, size_of_intermediate_matrice / 2, 0);
    copying_values_to_matrice(size_of_intermediate_matrice / 2, podmatrice_4_of_fouth, fouth_matrice, size_of_intermediate_matrice / 2, size_of_intermediate_matrice / 2);

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////////Создание промежуточных матриц//////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** intermediate_matrice_1 = new int* [size_of_intermediate_matrice / 2];
    int** intermediate_matrice_2 = new int* [size_of_intermediate_matrice / 2];
    int** intermediate_matrice_3 = new int* [size_of_intermediate_matrice / 2];
    int** intermediate_matrice_4 = new int* [size_of_intermediate_matrice / 2];
    int** intermediate_matrice_5 = new int* [size_of_intermediate_matrice / 2];
    int** intermediate_matrice_6 = new int* [size_of_intermediate_matrice / 2];
    int** intermediate_matrice_7 = new int* [size_of_intermediate_matrice / 2];
    for (int i = 0; i < size_of_intermediate_matrice / 2; i++)
    {
        intermediate_matrice_1[i] = new int[size_of_intermediate_matrice / 2];
        intermediate_matrice_2[i] = new int[size_of_intermediate_matrice / 2];
        intermediate_matrice_3[i] = new int[size_of_intermediate_matrice / 2];
        intermediate_matrice_4[i] = new int[size_of_intermediate_matrice / 2];
        intermediate_matrice_5[i] = new int[size_of_intermediate_matrice / 2];
        intermediate_matrice_6[i] = new int[size_of_intermediate_matrice / 2];
        intermediate_matrice_7[i] = new int[size_of_intermediate_matrice / 2];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////Вычисление значений промежуточных матриц///////////////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size_of_intermediate_matrice / 2; i++)
    {
        for (int j = 0; j < size_of_intermediate_matrice / 2; j++)
        {
            intermediate_matrice_1[i][j] = 0;
            intermediate_matrice_2[i][j] = 0;
            intermediate_matrice_3[i][j] = 0;
            intermediate_matrice_4[i][j] = 0;
            intermediate_matrice_5[i][j] = 0;
            intermediate_matrice_6[i][j] = 0;
            intermediate_matrice_7[i][j] = 0;
            for (int z = 0; z < size_of_intermediate_matrice / 2; z++)
            {
                intermediate_matrice_1[i][j] += (podmatrice_1_of_therd[i][z] + podmatrice_4_of_therd[i][z]) * (podmatrice_1_of_fouth[z][j] + podmatrice_4_of_fouth[z][j]);
                intermediate_matrice_2[i][j] += (podmatrice_3_of_therd[i][z] + podmatrice_4_of_therd[i][z]) * podmatrice_1_of_fouth[z][j];
                intermediate_matrice_3[i][j] += podmatrice_1_of_therd[i][z] * (podmatrice_2_of_fouth[z][j] - podmatrice_4_of_fouth[z][j]);
                intermediate_matrice_4[i][j] += podmatrice_4_of_therd[i][z] * (podmatrice_3_of_fouth[z][j] - podmatrice_1_of_fouth[z][j]);
                intermediate_matrice_5[i][j] += (podmatrice_1_of_therd[i][z] + podmatrice_2_of_therd[i][z]) * podmatrice_4_of_fouth[z][j];
                intermediate_matrice_6[i][j] += (podmatrice_3_of_therd[i][z] - podmatrice_1_of_therd[i][z]) * (podmatrice_1_of_fouth[z][j] + podmatrice_2_of_fouth[z][j]);
                intermediate_matrice_7[i][j] += (podmatrice_2_of_therd[i][z] - podmatrice_4_of_therd[i][z]) * (podmatrice_3_of_fouth[z][j] + podmatrice_4_of_fouth[z][j]);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////Создание вспомогательных матриц/////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** auxiliary_matrice_1 = new int* [size_of_intermediate_matrice / 2];
    int** auxiliary_matrice_2 = new int* [size_of_intermediate_matrice / 2];
    int** auxiliary_matrice_3 = new int* [size_of_intermediate_matrice / 2];
    int** auxiliary_matrice_4 = new int* [size_of_intermediate_matrice / 2];
    for (int i = 0; i < size_of_intermediate_matrice / 2; i++)
    {
        auxiliary_matrice_1[i] = new int[size_of_intermediate_matrice / 2];
        auxiliary_matrice_2[i] = new int[size_of_intermediate_matrice / 2];
        auxiliary_matrice_3[i] = new int[size_of_intermediate_matrice / 2];
        auxiliary_matrice_4[i] = new int[size_of_intermediate_matrice / 2];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////Подсчет значений вспомогательных матриц из промежуточных///////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size_of_intermediate_matrice / 2; i++)
    {
        for (int j = 0; j < size_of_intermediate_matrice / 2; j++)
        {
            auxiliary_matrice_1[i][j] = intermediate_matrice_1[i][j] + intermediate_matrice_4[i][j] - intermediate_matrice_5[i][j] + intermediate_matrice_7[i][j];
            auxiliary_matrice_2[i][j] = intermediate_matrice_3[i][j] + intermediate_matrice_5[i][j];
            auxiliary_matrice_3[i][j] = intermediate_matrice_2[i][j] + intermediate_matrice_4[i][j];
            auxiliary_matrice_4[i][j] = intermediate_matrice_1[i][j] - intermediate_matrice_2[i][j] + intermediate_matrice_3[i][j] + intermediate_matrice_6[i][j];
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////Создание результирующей матрицы/////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** prefinal_matrice = new int* [size_of_intermediate_matrice];
    for (int i = 0; i < size_of_intermediate_matrice; i++)
    {
        prefinal_matrice[i] = new int[size_of_intermediate_matrice];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////Занесение информации из вспомогательных матриц в результирующую/////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size_of_intermediate_matrice / 2; i++)
    {
        for (int j = 0; j < size_of_intermediate_matrice / 2; j++)
        {
            prefinal_matrice[i][j] = auxiliary_matrice_1[i][j];
            prefinal_matrice[i][j + size_of_intermediate_matrice / 2] = auxiliary_matrice_2[i][j];
            prefinal_matrice[i + size_of_intermediate_matrice / 2][j] = auxiliary_matrice_3[i][j];
            prefinal_matrice[i + size_of_intermediate_matrice / 2][j + size_of_intermediate_matrice / 2] = auxiliary_matrice_4[i][j];
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////Выравнивание границ результирующей матрицы/////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int  width_of_final_matrice = size_of_intermediate_matrice, higth_of_final_matrice = size_of_intermediate_matrice;//раньше была ошибка и было равно 100, и если размер матрицы кратен 2, то
    //размер результирующей матрицы становился 100, и при копирывании возникала ошибка об обращении к несуществующим данным.
    aligning_the_bounds(size_of_intermediate_matrice, width_of_final_matrice, higth_of_final_matrice, prefinal_matrice);

    int** final_matrice = new int* [width_of_final_matrice];
    for (int i = 0; i < width_of_final_matrice; i++)
    {
        final_matrice[i] = new int[higth_of_final_matrice];
        for (int j = 0; j < higth_of_final_matrice; j++)
            final_matrice[i][j] = prefinal_matrice[i][j];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////Вывод результирующей матрицы////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    cout << "\nРезультирующая матрица\n\n";
    output_matrice(final_matrice, width_of_final_matrice, higth_of_final_matrice);
    system("pause");

    ///////////////////////////////////////////////////////////////////////////////
    /////////////////////Очистка динамической памяти///////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    delete_matrice(first_matrice,width_of_first_matrice);
    delete_matrice(second_matrice,width_of_second_matrice);
    delete_matrice(therd_matrice,size_of_intermediate_matrice);
    delete_matrice(fouth_matrice,size_of_intermediate_matrice);
    delete_matrice(prefinal_matrice,size_of_intermediate_matrice);
    delete_matrice(final_matrice,width_of_final_matrice);
    delete_matrice(podmatrice_1_of_therd,size_of_intermediate_matrice / 2);
    delete_matrice(podmatrice_2_of_therd,size_of_intermediate_matrice / 2);
    delete_matrice(podmatrice_3_of_therd,size_of_intermediate_matrice / 2);
    delete_matrice(podmatrice_4_of_therd,size_of_intermediate_matrice / 2);
    delete_matrice(podmatrice_1_of_fouth,size_of_intermediate_matrice / 2);
    delete_matrice(podmatrice_2_of_fouth,size_of_intermediate_matrice / 2);
    delete_matrice(podmatrice_3_of_fouth,size_of_intermediate_matrice / 2);
    delete_matrice(podmatrice_4_of_fouth,size_of_intermediate_matrice / 2);
    delete_matrice(auxiliary_matrice_1,size_of_intermediate_matrice / 2);
    delete_matrice(auxiliary_matrice_2,size_of_intermediate_matrice / 2);
    delete_matrice(auxiliary_matrice_3,size_of_intermediate_matrice / 2);
    delete_matrice(auxiliary_matrice_4,size_of_intermediate_matrice / 2);
    delete_matrice(intermediate_matrice_1,size_of_intermediate_matrice / 2);
    delete_matrice(intermediate_matrice_2,size_of_intermediate_matrice / 2);
    delete_matrice(intermediate_matrice_3,size_of_intermediate_matrice / 2);
    delete_matrice(intermediate_matrice_4,size_of_intermediate_matrice / 2);
    delete_matrice(intermediate_matrice_5,size_of_intermediate_matrice / 2);
    delete_matrice(intermediate_matrice_6,size_of_intermediate_matrice / 2);
    delete_matrice(intermediate_matrice_7,size_of_intermediate_matrice / 2);
}

int main()
{

    srand(time(NULL));
    system("chcp 1251");
    cout << "Вас приветствует программа" << endl <<
        "быстрого перемножения матриц методом Штрассена\n\n";
    calculation_of_matrices();
}
