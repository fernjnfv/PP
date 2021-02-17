#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void enter_matrix_size(int &width_of_matrix,int &height_of_matrix,int index_of_matrix)
{
    do
    {
        cout << "Введите размеры матрицы № "<< index_of_matrix << " (значение большьше 0)\n";
        cin >> width_of_matrix >> height_of_matrix;
    } while (width_of_matrix <= 0 || height_of_matrix <= 0);
}

void fill_of_matrix(int** first_matrix,int** second_matrix, int width_of_first_matrix, int height_of_first_matrix,
                         int width_of_second_matrix, int height_of_second_matrix)
{
    int matrix_filling_mode;
    do
    {
        cout << "Выберите способ заполнения матриц\n" <<
            "1 - Вручную \n2 - Случайным образом\n";
        cin >> matrix_filling_mode;
    } while (matrix_filling_mode != 1 && matrix_filling_mode != 2);

    if (matrix_filling_mode == 1)
    {
        for (int i = 0; i < width_of_first_matrix; i++)
            for (int j = 0; j < height_of_first_matrix; j++)
                cin >> first_matrix[i][j];
        for (int i = 0; i < width_of_second_matrix; i++)
            for (int j = 0; j < height_of_second_matrix; j++)
                cin >> second_matrix[i][j];
    }
    else
    {
        for (int i = 0; i < width_of_first_matrix; i++)
            for (int j = 0; j < height_of_first_matrix; j++)
                first_matrix[i][j] = rand() % 10;
        for (int i = 0; i < width_of_second_matrix; i++)
            for (int j = 0; j < height_of_second_matrix; j++)
                second_matrix[i][j] = rand() % 10;
    }
}

void output_matrix(int** matrix, int width_of_matrix, int height_of_matrix)
{
    for (int i = 0; i < width_of_matrix; i++)
    {
        for (int j = 0; j < height_of_matrix; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

void bring_matrix(int** new_matrix, int** old_matrix,int size_of_new_matrix, int width_of_old_matrix, int height_of_old_matrix)
{
    for (int i = 0; i < size_of_new_matrix; i++)
    {
        new_matrix[i] = new int[size_of_new_matrix];
        for (int j = 0; j < size_of_new_matrix; j++)
            new_matrix[i][j] = 0;
    }
    for (int i = 0; i < width_of_old_matrix; i++)
    {
        for (int j = 0; j < height_of_old_matrix; j++)
            new_matrix[i][j] = old_matrix[i][j];
    }
}
void copy_values_to_matrix(int size_of_new_matrix, int** new_matrix, int** old_matrix,int shift_i, int shift_j)
{
    for (int i = 0; i < size_of_new_matrix; i++)
    {
        new_matrix[i] = new int[size_of_new_matrix];
        for (int j = 0; j < size_of_new_matrix; j++)
            new_matrix[i][j] = old_matrix[i+shift_i][j+ shift_j];
    }
}

void delete_matrix(int** matrix, int width_of_matrix)
{
    for (int i = 0; i < width_of_matrix; i++)
        delete[] matrix[i];
    delete[] matrix;
}

void align_the_bounds(int size_of_matrix, int &bound_1, int& bound_2, int** old_matrix)
{
    int timed_1 = 0;
    int timed_2 = 0;
    int max_bound_1 = bound_1;
    int max_bound_2 = bound_2;
    for (int i = 0; i < size_of_matrix; i++)
    {
        timed_1 = 0;
        timed_2 = 0;
        for (int j = 0; j < size_of_matrix; j++)
        {
            if (old_matrix[i][j] != 0)
            {
                timed_1++;
                bound_1 = max_bound_1;
            }

            if (old_matrix[j][i] != 0)
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

void calculation_of_matrix()
{
    int width_of_first_matrix, height_of_first_matrix,
        width_of_second_matrix, height_of_second_matrix,
        size_of_intermediate_matrix = 2;


    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////Ввод размеров матрицы пользователем////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    enter_matrix_size(width_of_first_matrix, height_of_first_matrix, 1);
    enter_matrix_size(width_of_second_matrix, height_of_second_matrix, 1);

    int** first_matrix = new int* [width_of_first_matrix];
    int** second_matrix = new int* [width_of_second_matrix];
    for (int i = 0; i < width_of_first_matrix; i++)
        first_matrix[i] = new int[height_of_first_matrix];

    for (int i = 0; i < width_of_second_matrix; i++)
        second_matrix[i] = new int[height_of_second_matrix];

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////Выбор способа заполнения и заполнение матриц///////////////////
    ///////////////////////////////////////////////////////////////////////////////

    fill_of_matrix(first_matrix,second_matrix,width_of_first_matrix,
                        height_of_first_matrix,width_of_second_matrix, height_of_second_matrix);

    cout << "\nМатрица 1\n\n";
    output_matrix(first_matrix, width_of_first_matrix, height_of_first_matrix);
    cout << "\nМатрица 2\n\n";
    output_matrix(second_matrix, width_of_second_matrix, height_of_second_matrix);

    ///////////////////////////////////////////////////////////////////////////////
    /////////////////Приведение матриц к требуемому размеру////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    while (size_of_intermediate_matrix < width_of_first_matrix || size_of_intermediate_matrix < height_of_first_matrix
        || size_of_intermediate_matrix < width_of_second_matrix || size_of_intermediate_matrix < height_of_second_matrix)
        size_of_intermediate_matrix *= 2;
    int** third_matrix = new int* [size_of_intermediate_matrix];
    bring_matrix(third_matrix, first_matrix, size_of_intermediate_matrix, width_of_first_matrix, height_of_first_matrix);
    int** fourth_matrix = new int* [size_of_intermediate_matrix];
    bring_matrix(fourth_matrix, second_matrix, size_of_intermediate_matrix, width_of_second_matrix, height_of_second_matrix);

    cout << "Приведенные матрицы\n";
    cout << "\nМатрица 1\n\n";
    output_matrix(third_matrix, size_of_intermediate_matrix, size_of_intermediate_matrix);
    cout << "\nМатрица 2\n\n";
    output_matrix(fourth_matrix, size_of_intermediate_matrix, size_of_intermediate_matrix);

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** podmatrix_1_of_third = new int* [size_of_intermediate_matrix / 2];
    int** podmatrix_2_of_third = new int* [size_of_intermediate_matrix / 2];
    int** podmatrix_3_of_third = new int* [size_of_intermediate_matrix / 2];
    int** podmatrix_4_of_third = new int* [size_of_intermediate_matrix / 2];
    copy_values_to_matrix(size_of_intermediate_matrix / 2, podmatrix_1_of_third, third_matrix, 0, 0);
    copy_values_to_matrix(size_of_intermediate_matrix / 2, podmatrix_2_of_third, third_matrix, 0, size_of_intermediate_matrix / 2);
    copy_values_to_matrix(size_of_intermediate_matrix / 2, podmatrix_3_of_third, third_matrix, size_of_intermediate_matrix / 2, 0);
    copy_values_to_matrix(size_of_intermediate_matrix / 2, podmatrix_4_of_third, third_matrix, size_of_intermediate_matrix / 2, size_of_intermediate_matrix / 2);

    int** podmatrix_1_of_fourth = new int* [size_of_intermediate_matrix / 2];
    int** podmatrix_2_of_fourth = new int* [size_of_intermediate_matrix / 2];
    int** podmatrix_3_of_fourth = new int* [size_of_intermediate_matrix / 2];
    int** podmatrix_4_of_fourth = new int* [size_of_intermediate_matrix / 2];
    copy_values_to_matrix(size_of_intermediate_matrix / 2, podmatrix_1_of_fourth, fourth_matrix, 0, 0);
    copy_values_to_matrix(size_of_intermediate_matrix / 2, podmatrix_2_of_fourth, fourth_matrix, 0, size_of_intermediate_matrix / 2);
    copy_values_to_matrix(size_of_intermediate_matrix / 2, podmatrix_3_of_fourth, fourth_matrix, size_of_intermediate_matrix / 2, 0);
    copy_values_to_matrix(size_of_intermediate_matrix / 2, podmatrix_4_of_fourth, fourth_matrix, size_of_intermediate_matrix / 2, size_of_intermediate_matrix / 2);

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////////Создание промежуточных матриц//////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** intermediate_matrix_1 = new int* [size_of_intermediate_matrix / 2];
    int** intermediate_matrix_2 = new int* [size_of_intermediate_matrix / 2];
    int** intermediate_matrix_3 = new int* [size_of_intermediate_matrix / 2];
    int** intermediate_matrix_4 = new int* [size_of_intermediate_matrix / 2];
    int** intermediate_matrix_5 = new int* [size_of_intermediate_matrix / 2];
    int** intermediate_matrix_6 = new int* [size_of_intermediate_matrix / 2];
    int** intermediate_matrix_7 = new int* [size_of_intermediate_matrix / 2];
    for (int i = 0; i < size_of_intermediate_matrix / 2; i++)
    {
        intermediate_matrix_1[i] = new int[size_of_intermediate_matrix / 2];
        intermediate_matrix_2[i] = new int[size_of_intermediate_matrix / 2];
        intermediate_matrix_3[i] = new int[size_of_intermediate_matrix / 2];
        intermediate_matrix_4[i] = new int[size_of_intermediate_matrix / 2];
        intermediate_matrix_5[i] = new int[size_of_intermediate_matrix / 2];
        intermediate_matrix_6[i] = new int[size_of_intermediate_matrix / 2];
        intermediate_matrix_7[i] = new int[size_of_intermediate_matrix / 2];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////Вычисление значений промежуточных матриц///////////////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size_of_intermediate_matrix / 2; i++)
    {
        for (int j = 0; j < size_of_intermediate_matrix / 2; j++)
        {
            intermediate_matrix_1[i][j] = 0;
            intermediate_matrix_2[i][j] = 0;
            intermediate_matrix_3[i][j] = 0;
            intermediate_matrix_4[i][j] = 0;
            intermediate_matrix_5[i][j] = 0;
            intermediate_matrix_6[i][j] = 0;
            intermediate_matrix_7[i][j] = 0;
            for (int z = 0; z < size_of_intermediate_matrix / 2; z++)
            {
                intermediate_matrix_1[i][j] += (podmatrix_1_of_third[i][z] + podmatrix_4_of_third[i][z]) * (podmatrix_1_of_fourth[z][j] + podmatrix_4_of_fourth[z][j]);
                intermediate_matrix_2[i][j] += (podmatrix_3_of_third[i][z] + podmatrix_4_of_third[i][z]) * podmatrix_1_of_fourth[z][j];
                intermediate_matrix_3[i][j] += podmatrix_1_of_third[i][z] * (podmatrix_2_of_fourth[z][j] - podmatrix_4_of_fourth[z][j]);
                intermediate_matrix_4[i][j] += podmatrix_4_of_third[i][z] * (podmatrix_3_of_fourth[z][j] - podmatrix_1_of_fourth[z][j]);
                intermediate_matrix_5[i][j] += (podmatrix_1_of_third[i][z] + podmatrix_2_of_third[i][z]) * podmatrix_4_of_fourth[z][j];
                intermediate_matrix_6[i][j] += (podmatrix_3_of_third[i][z] - podmatrix_1_of_third[i][z]) * (podmatrix_1_of_fourth[z][j] + podmatrix_2_of_fourth[z][j]);
                intermediate_matrix_7[i][j] += (podmatrix_2_of_third[i][z] - podmatrix_4_of_third[i][z]) * (podmatrix_3_of_fourth[z][j] + podmatrix_4_of_fourth[z][j]);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////Создание вспомогательных матриц/////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** auxiliary_matrix_1 = new int* [size_of_intermediate_matrix / 2];
    int** auxiliary_matrix_2 = new int* [size_of_intermediate_matrix / 2];
    int** auxiliary_matrix_3 = new int* [size_of_intermediate_matrix / 2];
    int** auxiliary_matrix_4 = new int* [size_of_intermediate_matrix / 2];
    for (int i = 0; i < size_of_intermediate_matrix / 2; i++)
    {
        auxiliary_matrix_1[i] = new int[size_of_intermediate_matrix / 2];
        auxiliary_matrix_2[i] = new int[size_of_intermediate_matrix / 2];
        auxiliary_matrix_3[i] = new int[size_of_intermediate_matrix / 2];
        auxiliary_matrix_4[i] = new int[size_of_intermediate_matrix / 2];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////Подсчет значений вспомогательных матриц из промежуточных///////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size_of_intermediate_matrix / 2; i++)
    {
        for (int j = 0; j < size_of_intermediate_matrix / 2; j++)
        {
            auxiliary_matrix_1[i][j] = intermediate_matrix_1[i][j] + intermediate_matrix_4[i][j] - intermediate_matrix_5[i][j] + intermediate_matrix_7[i][j];
            auxiliary_matrix_2[i][j] = intermediate_matrix_3[i][j] + intermediate_matrix_5[i][j];
            auxiliary_matrix_3[i][j] = intermediate_matrix_2[i][j] + intermediate_matrix_4[i][j];
            auxiliary_matrix_4[i][j] = intermediate_matrix_1[i][j] - intermediate_matrix_2[i][j] + intermediate_matrix_3[i][j] + intermediate_matrix_6[i][j];
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////Создание результирующей матрицы/////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** prefinal_matrix = new int* [size_of_intermediate_matrix];
    for (int i = 0; i < size_of_intermediate_matrix; i++)
    {
        prefinal_matrix[i] = new int[size_of_intermediate_matrix];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////Занесение информации из вспомогательных матриц в результирующую/////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size_of_intermediate_matrix / 2; i++)
    {
        for (int j = 0; j < size_of_intermediate_matrix / 2; j++)
        {
            prefinal_matrix[i][j] = auxiliary_matrix_1[i][j];
            prefinal_matrix[i][j + size_of_intermediate_matrix / 2] = auxiliary_matrix_2[i][j];
            prefinal_matrix[i + size_of_intermediate_matrix / 2][j] = auxiliary_matrix_3[i][j];
            prefinal_matrix[i + size_of_intermediate_matrix / 2][j + size_of_intermediate_matrix / 2] = auxiliary_matrix_4[i][j];
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////Выравнивание границ результирующей матрицы/////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int  width_of_final_matrix = size_of_intermediate_matrix, higth_of_final_matrix = size_of_intermediate_matrix;//раньше была ошибка и было равно 100, и если размер матрицы кратен 2, то
    //размер результирующей матрицы становился 100, и при копирывании возникала ошибка об обращении к несуществующим данным.
    align_the_bounds(size_of_intermediate_matrix, width_of_final_matrix, higth_of_final_matrix, prefinal_matrix);

    int** final_matrix = new int* [width_of_final_matrix];
    for (int i = 0; i < width_of_final_matrix; i++)
    {
        final_matrix[i] = new int[higth_of_final_matrix];
        for (int j = 0; j < higth_of_final_matrix; j++)
            final_matrix[i][j] = prefinal_matrix[i][j];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////Вывод результирующей матрицы////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    cout << "\nРезультирующая матрица\n\n";
    output_matrix(final_matrix, width_of_final_matrix, higth_of_final_matrix);
    system("pause");

    ///////////////////////////////////////////////////////////////////////////////
    /////////////////////Очистка динамической памяти///////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    delete_matrix(first_matrix,width_of_first_matrix);
    delete_matrix(second_matrix,width_of_second_matrix);
    delete_matrix(third_matrix,size_of_intermediate_matrix);
    delete_matrix(fourth_matrix,size_of_intermediate_matrix);
    delete_matrix(prefinal_matrix,size_of_intermediate_matrix);
    delete_matrix(final_matrix,width_of_final_matrix);
    delete_matrix(podmatrix_1_of_third,size_of_intermediate_matrix / 2);
    delete_matrix(podmatrix_2_of_third,size_of_intermediate_matrix / 2);
    delete_matrix(podmatrix_3_of_third,size_of_intermediate_matrix / 2);
    delete_matrix(podmatrix_4_of_third,size_of_intermediate_matrix / 2);
    delete_matrix(podmatrix_1_of_fourth,size_of_intermediate_matrix / 2);
    delete_matrix(podmatrix_2_of_fourth,size_of_intermediate_matrix / 2);
    delete_matrix(podmatrix_3_of_fourth,size_of_intermediate_matrix / 2);
    delete_matrix(podmatrix_4_of_fourth,size_of_intermediate_matrix / 2);
    delete_matrix(auxiliary_matrix_1,size_of_intermediate_matrix / 2);
    delete_matrix(auxiliary_matrix_2,size_of_intermediate_matrix / 2);
    delete_matrix(auxiliary_matrix_3,size_of_intermediate_matrix / 2);
    delete_matrix(auxiliary_matrix_4,size_of_intermediate_matrix / 2);
    delete_matrix(intermediate_matrix_1,size_of_intermediate_matrix / 2);
    delete_matrix(intermediate_matrix_2,size_of_intermediate_matrix / 2);
    delete_matrix(intermediate_matrix_3,size_of_intermediate_matrix / 2);
    delete_matrix(intermediate_matrix_4,size_of_intermediate_matrix / 2);
    delete_matrix(intermediate_matrix_5,size_of_intermediate_matrix / 2);
    delete_matrix(intermediate_matrix_6,size_of_intermediate_matrix / 2);
    delete_matrix(intermediate_matrix_7,size_of_intermediate_matrix / 2);
}

int main()
{

    srand(time(NULL));
    system("chcp 1251");
    cout << "Вас приветствует программа" << endl <<
        "быстрого перемножения матриц методом Штрассена\n\n";
    calculation_of_matrix();
}
