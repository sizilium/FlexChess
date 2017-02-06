/**
 * @file Matrix.hpp
 * File provides a simple template Matrix class, whith two dimensions
 * and several usefully function how work on the matrix template.
 *
*/

#ifndef MATRIX_H
#define MATRIX_H

// includes
#include <vs/Build.hpp>
#include <vs/base/cont/JavaStyleIterator.hpp>
#include <vs/base/cont/JavaStyleContainer.hpp>
#include <vs/base/cont/NullIterator.hpp>
#include <iostream>
#include <assert.h>
#include <vector>
#include <iomanip>
#include <utility>
#include <cstdlib>
#include <stdarg.h>

namespace vs
{
namespace base
{
namespace cont
{
// predeclarations
template<class T> class Matrix;

/**
 * Global function wich swappes two matrices.
 */
template<class T>
VS_EXPORT void swap(Matrix<T> &matrix_1, Matrix<T> &matrix_2)
{
	Matrix<T> tmp = matrix_2;
	matrix_2 = matrix_1;
	matrix_1 = tmp;
}


/**
 * @class Matrix 
 * 2d matrix container for any types. rows and columns are free available.
 */
template <class T>
class VS_EXPORT Matrix: public JavaStyleContainer<T>
{
public:

	/**
	 * Creates a empty matrix.
	 */
	Matrix()
	{
		rows = 0;
		columns = 0;
	}

	/**
	 * Creates the 2d matrix with unrestricted row- and column-size.\n
	 * @param setRows number of rows
	 * @param setColumns number of columns
	 * @param initValues Default is 0. All elements of the matrix will init with this value.
	 */
	Matrix(int setRows, int setColumns, const T &initValues = T())
	{
		assert (setRows > 0 && setColumns > 0);
		rows = setRows;
		columns = setColumns;
		for (int i = 0; i < rows * columns; i++)
			matrix.push_back(initValues);
	}
	virtual ~Matrix()
	{}
	
	/**
	 * Checks if two matrices have the same content.
	 * @return True if it != op2
	 */
	bool operator== (const Matrix<T>& op2) const
	{
		return (this->rows == op2.rows && this->columns == op2.columns && this->matrix == op2.matrix);
	}

	/**
	 * The opposite of '==' operator. Checks if two matrices have different content.
	 * @return True if it != op2
	 */
	bool operator!= (const Matrix<T> &op2) const
	{
		return (this->rows != op2.rows || this->columns != op2.columns || this->matrix != op2.matrix);
	}
	
// TODO matrix operators for common matrix math (scalar, multipliing, adition etc.)
//	Matrix<T> &operator+=(const Matrix<T> &matrix);
//	Matrix<T> operator+(const DoubleVector &matrix) const;
//
//	Matrix<T> &operator-=(const Matrix<T> &matrix);
//	Matrix<T> operator-(const Matrix<T> &matrix) const;
//
//	Matrix<T> &operator*=(const double &scalar);
//	Matrix<T> operator*(const double &scalar) const;
//
//	Matrix<T> &operator/=(const double &scalar);
//	Matrix<T> operator/(const double &scalar) const;
//
//	Matrix<T> &operator=(const Matrix<T> &matrix);
//
//	//double &operator[](unsigned int n);
//
//	double operator*(const Matrix<T> &matrix);
	
	/**
	 * The Matrix iterator iterates line by line:\n
	 * 1 2 3\n
	 * 4 5 6\n
	 * 7 8 9\n
	 * It's a stl bidirectional iterator, so you can apply stl algorithms. It's a JavaStyleIterator
	 * too.
	 * @code // Example
	 * Matrix<int> matrix(4, 4);
	 * // stl generate algorithm
	 * generate(matrix.begin(), matrix.end(), myFunc);	// myFunc might fill the matrix with random numbers for example
	 * @endcode
	 */
	class VS_EXPORT Iterator : public JavaStyleIterator<T>, public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:	
		// typedefs
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef int difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		friend class Matrix<T>;

		/**
		 * Constructor for uninitialized iterator. Before using initialize it first (else an 
		 * assertion will fail). 
		 */
		Iterator()
		:row(0), column(0), matrix(NULL)
		{
		}
		
		/**
		 * Iterator to matrix index (0, 0) by default.
		 * @param row Start row.
		 * @param column Start column.
		 */
		Iterator(Matrix<T> *matrix, int row = 0, int column = 0)
		:row(row), column(column), matrix(matrix)
		{
			assert("Iterator wrong initialized. Index out of range!" && row < matrix->rows && column < matrix->columns);
		}

		/**
		 * Checks if there is a next element in the matrix.
		 */
		bool hasNext() const
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			return (column < matrix->columns && row < matrix->rows);
		}

		/**
		 * Returns the current element.
		 */
		T current() const
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			return matrix->get(row, column);
		}
		
		/**
		 * Returns at the first the current element and then goes to next.
		 */
		T next()
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			T retVal = matrix->get(row, column);
			++column;
			if (column == matrix->columns)
			{
				assert("There is no next element in the matrix. First check with hasNext()!" && row < matrix->rows);
				column = 0;
				++row;
			}
			return retVal;
		}

		void remove()
		{
			// TODO remove for matrix iterator
		}

		/**
		 * Returns a reference to the current element.
		 */
		reference operator*() const
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			return matrix->get(row, column);
		}

		/**
		 * Returns a pointer to the current element.
		 */
		pointer operator->() const
		{
			return &(operator*()); 
		}

		/**
		 * Prefix increment. Returns the iterator reference.
		 */
		Iterator& operator++()
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			++column;
			if (column == matrix->columns)
			{
				assert("There is no next element in the matrix. First check with end() iterator!" && row < matrix->rows);
				column = 0;
				++row;
			}
			return *this;
		}
		
		/**
		 * Prefix decrement. Returns the iterator reference.
		 */
		Iterator& operator--()
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			--column;
			if (column < 0 )
			{
				assert("There is no previous element in the matrix." && row >= 0);
				column = matrix->numColumns() - 1;
				-- row;
			}
			return *this;
		}
		
		/**
		 * Postfix increment. Returns the iterator.
		 */
		Iterator operator++(int)
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			Iterator tmp = *this;
			++column;
			if (column == matrix->columns)
			{
				assert("There is no next element in the matrix. First check with end() iterator" && row < matrix->rows);
				column = 0;
				++row;
			}
			return tmp;
		}
		
		/**
		 * Postfix decrement. Returns the iterator.
		 */
		Iterator operator--(int)
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			Iterator tmp = *this;
			--column;
			if (column < 0 )
			{
				assert("There is no next element in the matrix" && row >= 0);
				column = matrix->numColumns() - 1;
				-- row;
			}
			return tmp;
		}
		
		bool operator== (const Iterator& op2) const
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			if (row == op2.row && column == op2.column && matrix == op2.matrix)
				return true;
			else 
				return false;
		}

		bool operator!= (const Iterator &op2) const
		{
			return !(*this == op2);
		}
			
	private:
		int row, column;
		Matrix<T> *matrix;
	};
	

	class VS_EXPORT Const_Iterator : public JavaStyleIterator<T>, public std::iterator<std::bidirectional_iterator_tag, const T>
	{
	public:
		// typedefs
		typedef const T value_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef int difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		friend class Matrix<T>;
		
		/**
		 * Constructor for uninitialized iterator. Before using initialize it first (else an 
		 * assertion will fail). 
		 */
		Const_Iterator()
		:row(0), column(0), matrix(NULL)
		{
		}
		
		/**
		 * Iterator to matrix index (0, 0) by default.
		 * @param row Start row.
		 * @param column Start column.
		 */
		Const_Iterator(Matrix<T> *matrix, int row = 0, int column = 0)
		:row(row), column(column), matrix(matrix)
		{
			assert("Iterator wrong initialized. Index out of range!" && row < matrix->rows && column < matrix->columns);
		}
		
		/**
		 * Checks if there is a next element in the matrix.
		 */
		bool hasNext() const
		{
			assert("Const_Iterator is uninitialized. First call begin() for example!" && matrix);
			return (column < matrix->columns && row < matrix->rows);
		}
		
		/**
		 * Returns the current element.
		 */
		T current() const
		{
			assert("Const_Iterator is uninitialized. First call begin() for example!" && matrix);
			return matrix->get(row, column);
		}

		/**
		 * Returns at the first the current element and then goes to next.
		 */
		T next()
		{
			assert("Const_Iterator is uninitialized. First call begin() for example!" && matrix);
			T retVal = matrix->get(row, column);
			++column;
			if (column == matrix->columns)
			{
				assert("There is no next element in the matrix. First check with hasNext()!" && row < matrix->rows);
				column = 0;
				++row;
			}
			return retVal;
		}

		void remove()
		{
			// nothing
		}

		/**
		 * Returns a reference to the current element.
		 */
		reference operator*() const
		{
			assert("Const_Iterator is uninitialized. First call begin() for example!" && matrix);
			return matrix->get(row, column);
		}

		/**
		 * Returns a pointer to the current element.
		 */
		pointer operator->() const
		{
			return &(operator*()); 
		}

		/**
		 * Prefix increment. Returns the iterator reference.
		 */
		Const_Iterator& operator++()
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			++column;
			if (column == matrix->columns)
			{
				assert("There is no next element in the matrix. First check with end() iterator!" && row < matrix->rows);
				column = 0;
				++row;
			}
			return *this;
		}
		
		/**
		 * Prefix decrement. Returns the iterator reference.
		 */
		Const_Iterator& operator--()
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			--column;
			if (column < 0 )
			{
				assert("There is no previous element in the matrix." && row >= 0);
				column = matrix->numColumns() - 1;
				-- row;
			}
			return *this;
		}
		
		/**
		 * Postfix increment. Returns the iterator.
		 */
		Const_Iterator operator++(int)
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			Iterator tmp = *this;
			++column;
			if (column == matrix->columns)
			{
				assert("There is no next element in the matrix. First check with end() iterator" && row < matrix->rows);
				column = 0;
				++row;
			}
			return tmp;
		}
		
		/**
		 * Postfix decrement. Returns the iterator.
		 */
		Const_Iterator operator--(int)
		{
			assert("Iterator is uninitialized. First call begin() for example!" && matrix);
			Iterator tmp = *this;
			--column;
			if (column < 0 )
			{
				assert("There is no next element in the matrix" && row >= 0);
				column = matrix->numColumns() - 1;
				-- row;
			}
			return tmp;
		}
		
		bool operator== (const Const_Iterator& op2) const
		{
			assert("Const_Iterator is uninitialized. First call begin() for example!" && matrix);
			if (row == op2.row && column == op2.column && matrix == op2.matrix)
				return true;
			else 
				return false;
		}

		bool operator!= (const Const_Iterator &op2) const
		{
			return !(*this == op2);
		}
		
	private:
		int row;
		int column;
		// this is const!
		const Matrix *matrix;
	};
	
	
	// -------------- Java section ------------------
	
	/**
	 * Returns a SmartIterator to the first element of the matrix (0, 0) or a NullIterator (a
	 * special SmartIterator) if the matrix is empty.
	 */
	SmartIterator<T> iterator() const
	{
		if (empty())
			return SmartIterator<T> (new NullIterator<T>);
		else
			return SmartIterator<T> (new Iterator(const_cast<Matrix*>(this)) );
	}
	
	/**
	 * Adds an element to the end of the matrix.
	 */
	void add(const T element)
	{
		// TODO add method for matrix
	}
	
	bool remove(const T value)
	{
		// TODO remove method for matrix
		return false;
	}
	
	// ----------- Java section end ----------------
	
	/**
	 * Returns a matrix iterator to the first element of the matrix (0, 0).
	 */
	Iterator begin()
	{
		return Iterator(this);
	}
	
	/**
	 * Returns a matrix iterator to the last element of the matrix (numRows - 1, numColumns - 1).
	 */
	Iterator end()
	{
		return Iterator(this, rows - 1, columns - 1);
	}
	
	/**
	 * Returns a const matrix iterator to the first element of the matrix (0, 0).
	 */
	Const_Iterator begin() const
	{
		return Const_Iterator(this);
	}
	
	/**
	 * Returns a const matrix iterator to the last element of the matrix 
	 * (numRows - 1, numColumns - 1).
	 */
	Const_Iterator end() const
	{
		return Const_Iterator(this, rows - 1, columns - 1);
	}
	

	/**
	 * clears the contents an sets the size of rows and columns to 0
	 */
	void clear()
	{
		matrix.clear();
		rows = 0;
		columns = 0;
	}

	/**
	 * resizes the matrix safely, old contents will not loose (except you
	 * reduce the size)
	 */
	void resize(int newRowSize, int newColumnSize, const T &newValues = T())
	{
		std::vector<T> tmp = matrix;
		tmp = matrix;

		matrix.clear();
		matrix.resize(newRowSize * newColumnSize);
		
		// obtain values from the old matrix
        for (int y = 0; y < (rows < newRowSize ? rows : newRowSize) ; y++)
            for (int x = 0; x < (columns < newColumnSize ? columns : newColumnSize) ; x++)
                matrix.at(y * newColumnSize + x) = tmp.at(y * columns + x);

        rows = newRowSize;
		columns = newColumnSize;
	}

	/**
	 * @return number of rows in int
	 */
	int numRows() const
	{
		return rows;
	}
	/**
	 * @return number of columns in int
	 */
	int numColumns() const
	{
		return columns;
	}
	
	/**
	 * Returns the number of element in the matrix. This is simply numRows * numColumns.
	 */
	int size() const
	{
		return rows * columns;
	}

	/**
	 * Checks if the matrix is empty. Thats the case if numRows and numColumns are 0.
	 */
	bool empty() const
	{
		if (rows == 0 && columns == 0)
			return true;
		else
			return false;
	}
	
	/**
	 * Setter for matrix elements.
	 * @param value Pass the value to set in the matrix.
	 * @param row Row number of matrix (starts with 0).
	 * @param column Column number of matrix (starts with 0).
	 */
	void set(const T &value, int row, int column)
	{
		assert(row < rows && row >= 0 && column < columns && column >= 0);
		matrix.at(row * columns + column) = value;
	}

	/**
	 * @param Converts an old c-array ( int m[] = {...}; ) in this matrix container.
	 */
	void set(T *intMatrix)
	{
		for (int i = 0; i < rows * columns; i++)
			matrix.at(i) = *(intMatrix + i);
	}
	
	/**
	 * Sets a row with values given by parameter. The number of parameter are variable
	 * (c++ ellipse), but consider the dimensions.
	 * @param row The row number to fill with the follow parameters ...
	 * @param numColumns The number of follow columns, passed by parameter.
	 */
	void setRow(int row, int numColumns, ...)
	{
		assert("Invalid row or numColumns for setRow() method. Check the matrix dimension!" && row >= 0 && row < rows && numColumns > 0 && numColumns <= columns);
		va_list ap;
		va_start(ap, numColumns);
		for (int i = 0; i < numColumns; i++)
		{
			matrix.at(row * columns + i) = va_arg(ap, T);
		}
		
		va_end(ap);
	}
	
	/**
	 * Sets a column with values given by parameter. The number of parameter are variable
	 * (c++ ellipse), but consider the dimensions.
	 * @param column The column number to fill with the follow parameters ...
	 * @param numRows The number of follow rows, passed by parameter.
	 */
	void setColumn(int column, int numRows, ...)
	{
		assert("Invalid row or numColumns for setColumn() method. Check the matrix dimension!" && column >= 0 && column < columns && numRows > 0 && numRows <= rows);
		va_list ap;
		va_start(ap, numRows);
		for (int i = 0; i < numRows; i++)
		{
			matrix.at(i * columns + column) = va_arg(ap, T);
		}
		
		va_end(ap);
	}
	
	/**
	 * Getter for reference to value.
	 * @return Copy of value.
     * @param row The y-index of matrix
     * @param column The x-index of matrix
	 */
	T& get(int row, int column)
	{
		assert("Wrong row or column for matrix (out of range)!" && row < rows && row >= 0 && column < columns && column >= 0);
		return matrix.at(row * columns + column);
	}
	
	/**
	 * Getter for value (const).
	 * @return Copy of value.
     * @param row The y-index of matrix
     * @param column The x-index of matrix
	 */
	T get(int row, int column) const
	{
		assert("Wrong row or column for matrix (out of range)!" && row < rows && row >= 0 && column < columns && column >= 0);
		return matrix.at(row * columns + column);
	}
	
	void transpose()
	{
		// TODO matrix transpose method implementation
	}
	
	T determinant()
	{
		// TODO matrix determinant method implementation
	}
	
	/**
	 * Fills the hole matrix with a specified value.
	 * @code // Example
	 * Matrix<int> matrix(3, 3);
	 * matrix.fill(5);
	 * // 5 5 5
	 * // 5 5 5
	 * // 5 5 5
	 * @endcode
	 */
	void fill(const T& value = T())
	{
		for (int y = 0; y < rows; y++)
			for (int x = 0; x < columns; x++)
				get(y, x) = value;
	}
	
	/**
	 * Fills a single column of the matrix with a specified value.
	 * @code // Example
	 * Matrix<int> matrix(3, 3);
	 * matrix.fillColumn(1, 7);
	 * // 0 7 0
	 * // 0 7 0
	 * // 0 7 0
	 * @endcode
	 */
	void fillColumn(int column, const T &value = T())
	{
		for (int y = 0; y < rows; y++)
			get(y, column) = value;
	}

	/**
	 * Fills a single row of the matrix with a specified value.
	 * @code // Example
	 * Matrix<int> matrix(3, 3);
	 * matrix.fillColumn(2, 3);
	 * // 0 0 0
	 * // 0 0 0
	 * // 3 3 3
	 * @endcode
	 */
	void fillRow(int row, const T &value = T())
	{
		for (int x = 0; x < columns; x++)
			get(row, x) = value;
	}
	
	/**
	 * Fills the leading diagonal of the matrix with a specified value.
	 * @code // Example
	 * Matrix<int> matrix(3, 3);
	 * matrix.fillLeadingDiagonal(9);
	 * // 0 0 9
	 * // 0 9 0
	 * // 9 0 0
	 * @endcode
	 */
	void fillLeadingDiagonal(const T &value = T())
	{
		for (int x = 0, y = rows-1; x < columns && y >= 0; x++, y--)
			get(y, x) = value;
	}
	
	/**
	 * Fills the trailing diagonal of the matrix with a specified value.
	 * @code // Example
	 * Matrix<int> matrix(3, 3);
	 * matrix.fillTrailingDiagonal(6);
	 * // 6 0 0
	 * // 0 6 0
	 * // 0 0 6
	 * @endcode
	 */
	void fillTrailingDiagonal(const T &value = T())
	{
		for (int x = 0, y = 0; x < columns && y < rows; x++, y++)
			get(y, x) = value;
	}
	
	/**
	 * Fills the trailing diagonal of the matrix with a specified value.
	 * @code // Example
	 * Matrix<int> matrix(3, 3);
	 * matrix.makeIdentity(1);
	 * // 1 0 0
	 * // 0 1 0
	 * // 0 0 1
	 * 
	 * matrix.makeIdentity(5, 1);
	 * // 5 1 1
	 * // 1 5 1
	 * // 1 1 5
	 * @endcode
	 */
	void makeIdentity(const T &one, const T &zero = T())
	{
		fill(zero);
		fillTrailingDiagonal(one);
	}

	/**
	 * Print the matrix values to the console std stream.
	 */
	void coutDebug() const
	{
		std::cout.precision(5);
		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < columns; x++)
			{
				std::cout << std::setw(4) << matrix.at(y * columns + x) << " ";
			}
			std::cout << std::endl;
		}
	}

	friend void vs::base::cont::swap<T>(Matrix<T> &matrix_1, Matrix<T> &matrix_2);

private:
	int rows, columns;
	std::vector<T> matrix;
};


/**
 * The function simply calcs the index by given
 * row and column number and a matrix (you only have to pass the matrix without
 * remaining the matrix size)
 */
template <class T>
int rowColumnToIndex(Matrix<T> &matrix, int row, int column)
{
	assert(row >= 0 && column >= 0 && row < matrix.rowSize() && column < matrix.columnSize()
		   && "row||columns exeeds limit of the given matrix!");
	return row * matrix.columnSize() + column;
}


/**
 * The function simpy calcs the row and column
 * of a given matrix and index number (you only have to pass the matrix without
 * remaining the matrix size)
 */
template <class T>
std::pair<int, int> indexToRowColumn(Matrix<T> &matrix, int index)
{
	assert(index < matrix.rowSize() * matrix.columnSize() && index >= 0 &&
		   "index exeeds limits of the given matrix!");
	std::pair<int, int> retVal;

	div_t result = div( index, matrix.rowSize() );

	retVal.first = result.quot;
	retVal.second = result.rem;

	return retVal;
}


/**
 * Converts a common symmetrical 2d Matrix (each field represents a node
 * with edges to each neighbour fields) in a adjacency 2d Matrix.\n
 * Note: These function needs the Matrix.cpp source file!
 * @param matrix A integer matrix (TODO template)
 * @param retMatrix result Adjacency int matrix as reference. The size of output
 * will be the square of input matrix. You can pass the retMatrix with any size
 * (resizes automatically)
 */
void convertMatrixToAdjacencyMatrix(const Matrix<int> &matrix, Matrix<int> &retMatrix);


} // cont
} // base
} // vs


#endif
