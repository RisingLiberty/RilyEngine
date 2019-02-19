#pragma once

namespace Math
{


template <int rows, int columns, typename T = float>
struct Matrix
{
	Matrix() = default;
	Matrix(T* data)
	{
		memcpy(m, data, rows * columns * sizeof(T));
	}
	Matrix(std::array<T, rows * columns> arr)
	{
		memcpy(m, &arr[0], rows * columns * sizeof(T));
	}
	Matrix(T data[rows][columns])
	{
		memcpy(m, data, rows * columns * sizeof(T));
	}
	Matrix(const Matrix& mat)
	{
		memcpy(m, mat.m, rows * columns * sizeof(T));
	}
	Matrix(const Matrix&& mat)
	{
		memcpy(m, mat.m, rows * columns * sizeof(T));
	}

	Matrix& operator=(const Matrix& mat)
	{
		memcpy(m, mat.m, rows * columns * sizeof(T));
		return *this;
	}
	Matrix& operator=(const Matrix&& mat)
	{
		memcpy(m, mat.m, rows * columns * sizeof(T));
		return *this;
	}


	template <int otherColums>
	Matrix <rows, otherColums, T> operator*(const Matrix<columns, otherColums, T>& mat) const
	{
		//2x2 * 2x3 = 2x3
		//for this rows
		//for other columns
		//this.columns has to be equal to other.rows

		Matrix<rows, otherColums, T> newMat;
		T data[rows][otherColums];

		for (int row = 0; row < rows; ++row)
		{
			for (int column = 0; column < otherColums; ++column)
			{
				float sum = 0;

				for (int i = 0; i < columns; ++i)
					sum += m[row][i] * mat.m[i][column];

				data[row][column] = sum;
			}
		}
		memcpy(newMat.m, data, rows * otherColums * sizeof(T));
		return newMat;
	}
	Matrix operator*(const T scalar)
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				m[i][j] *= scalar;
			}
		}

		return *this;
	}
	template <int otherColumns>
	Matrix <rows, otherColumns, T> operator*=(const Matrix<columns, otherColumns, T>& mat)
	{
		*this = *this * mat;
		return *this;
	}
	Matrix operator*=(const T scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	float GetDeterminant() const
	{
		if (rows != columns)
			assert(false); //this is not possible

		if (rows < 2 || columns < 2)
			return 0;

		if (rows == 2)
			return m[0][0] * m[1][1] - m[0][1] * m[1][0];

		//create a matrix of current dimension - 1
		float det = 0;
		bool add = true;

		for (int column = 0; column < columns; ++column)
		{
			Matrix<rows - 1, columns - 1, T> newMat;
			const int nrOfRows = rows - 1;
			const int nrOfColumns = columns - 1;
			float data[nrOfRows][nrOfColumns] = {};
			float value = m[0][column];

			//fill new matrix
			//always start at the 2nd row
			//ignore current collumn

			int dataRow = 0;
			for (int i = 1; i < rows; ++i)
			{
				int dataColumn = 0;
				for (int j = 0; j < columns; ++j)
				{
					//skip if we're at current collumn
					if (j == column)
					{
						continue;
						//if all collums have already been filled, we don't need to loop further, so we End here.
						//if (dataColumn == nrOfRows) break;

						//++j;
						//set j back to 0 if we're going out of scope
						//if (j > columns)
						//	j = 0;
					}
					//set j back to 0 if we're going out of scope
					if (j > columns)
						j = 0;


					data[dataRow][dataColumn] = m[i][j];
					++dataColumn;
				}
				++dataRow;
			}
			newMat = data;
			if (add)
				det += value * newMat.GetDeterminant();
			else
				det -= value * newMat.GetDeterminant();

			add = !add;
		}

		return det;
	}

	Matrix GetInverse() const
	{
		float det = this->GetDeterminant();

		if (det == 0)
			return Matrix();

		float detInv = 1 / det;
	
		Matrix mm = this->GetMatrixOfMinors();
		mm.ApplyCoFactors();
		mm = mm.GetTranspose();

		mm *= detInv;

		return mm;
	}
	Matrix GetMatrixOfMinors() const
	{
		float data[rows][columns] = {};
		Matrix newMat;
		bool negative = false;

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				//create smaller matrix
				float smallerData[rows - 1][columns - 1] = {};
				int dataRow = 0;
				Matrix<rows - 1, columns - 1, T> smallMatrix;
				for (int row = 0; row < rows; ++row)
				{
					if (row == i)
						continue;

					int dataColumn = 0;

					for (int column = 0; column < columns; ++column)
					{
						if (column == j)
							continue;

						smallerData[dataRow][dataColumn] = m[row][column];
						++dataColumn;
					}
					++dataRow;
				}

				smallMatrix = smallerData;
				float det = smallMatrix.GetDeterminant();

				newMat.m[i][j] = det;
			}
		}

		return newMat;
	}

	void ApplyCoFactors()
	{
		bool negative = false;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				int sign = (int)pow(-1, i + j);
				m[i][j] *= sign;
			}
		}
	}

	Matrix<columns, rows, T> GetTranspose() const
	{
		Matrix mat;
		for (int i = 0; i < columns; ++i)
		{
			for (int j = 0; j < rows; ++j)
			{
				mat.m[i][j] = m[j][i];
			}
		}
		return mat;
	}
	
	T* operator[](int id) const { return m[id]; }

	friend std::ostream& operator<<(std::ostream& os, Matrix mat)
	{
		for (int i = 0; i < rows; ++i)
		{
			os << "|";
			for (int j = 0; j < columns; ++j)
			{
				if (abs(mat.m[i][j]) > 0.0001f)
					os << "\t" << mat.m[i][j] << ", ";
				else
					os << "\t0,";
			}
			os << "\t|\n";
		}
		return os;
	}
public:
	T m[rows][columns];
};

template <typename T>
struct Matrix<0, 0, T>
{
	float GetDeterminant() { return 0; }

public:
	T m[1][1];
};

template <typename T>
struct Matrix<1, 1, T>
{
	float GetDeterminant() { return 0; }

public:
	T m[1][1];
};


template <typename T>
struct Matrix<2, 2, T>
{
	Matrix() = default;
	Matrix(T data[2][2])
	{
		memcpy(m, data, 2 * 2 * sizeof(T));
	}
	Matrix(const Matrix& mat)
	{
		memcpy(m, mat.m, 2 * 2 * sizeof(T));
	}
	Matrix(const Matrix&& mat)
	{
		memcpy(m, mat.m, 2 * 2 * sizeof(T));
	}
	Matrix& operator=(const Matrix& mat)
	{
		memcpy(m, mat.m, 2 * 2 * sizeof(T));
		return *this;
	}
	Matrix& operator=(const Matrix&& mat)
	{
		memcpy(m, mat.m, 2 * 2 * sizeof(T));
		return *this;
	}

	template <int otherColums>
	Matrix <2, otherColums, T> operator*(const Matrix<2, otherColums, T>& mat) const
	{
		//2x2 * 2x3 = 2x3
		//for this rows
		//for other columns
		//this.columns has to be equal to other.rows

		Matrix<2, otherColums, T> newMat;
		T data[2][otherColums];

		for (int row = 0; row < 2; ++row)
		{
			for (int column = 0; column < otherColums; ++column)
			{
				float sum = 0;

				for (int i = 0; i < 2; ++i)
					sum += m[row][i] * mat.m[i][column];

				data[row][column] = sum;
			}
		}
		memcpy(newMat.m, data, 2 * otherColums * sizeof(T));
		return newMat;
	}
	T GetDeterminant() { return m[0][0] * m[1][1] - m[0][1] * m[1][0]; }

	Matrix GetInvesere() const
	{
		T det = GetDeterminant();
		if (det == 0)
			assert(false);

		float data[2][2];

		float detInv = 1 / det;
		data[0][0] = detInv * m[1][1];
		data[0][1] = detInv * -m[0][1];
		data[1][0] = detInv * (-m[1][0]);
		data[1][1] = detInv * m[0][0];

		return Matrix(data);
	}

	friend std::ostream& operator<<(std::ostream& os, Matrix mat)
	{
		os << "|\t";
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				if (abs(mat.m[i][j]) > 0.0001f)
					os << mat.m[i][j] << ", ";
				else
					os << "0,";
			}
			os << "\t|\n\t";
		}
		return os;
	}

public:
	T m[2][2];
};


typedef Matrix<4, 4, float> Mat44;
typedef Matrix<3, 3, float> Mat33;
typedef Matrix<2, 2, float> Mat22;

typedef Matrix<4, 4, double> Mat44d;
typedef Matrix<3, 3, double> Mat33d;
typedef Matrix<2, 2, double> Mat22d;

}
