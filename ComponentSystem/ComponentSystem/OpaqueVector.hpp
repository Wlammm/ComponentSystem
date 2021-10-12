#pragma once
#include <assert.h>

namespace CommonUtilities
{
	class OpaqueVector
	{
	public:
		OpaqueVector() = default;
			
		~OpaqueVector()
		{
			assert(myData == nullptr && "You must manually call Destroy() on all opaque vectors before running the destructor.");
		}

		template<typename T>
		void Init(size_t aReservedNrOfElements = 4)
		{
			assert(!myData && L"This opaque vector is already initialized");

			myElementSize = sizeof(T);
			myMaxNrOfElements = aReservedNrOfElements;
			myData = new char[aReservedNrOfElements * myElementSize];
			myNrOfElements = 0;
		}

		template<typename T>
		void Destroy()
		{
			for (size_t i = 0; i < myNrOfElements; i++)
			{
				T* objectPointer = reinterpret_cast<T*>(&myData[i * myElementSize]);
				objectPointer->~T();
			}
			delete[] myData;
			myData = nullptr;
			myElementSize = 0;
			myMaxNrOfElements = 0;
			myNrOfElements = 0;
		}

		template<typename T>
		T* EmblaceBack()
		{
			if (myEmptyIndexes.size() != 0)
			{
				T* newT = new (&myData[myEmptyIndexes.back() * myElementSize]) T();
				myEmptyIndexes.pop_back();
				return newT;
			}

			T* newT = new (&myData[myNrOfElements * myElementSize]) T();
			myNrOfElements++;
			return newT;
		}

		template<typename T>
		void Remove(const unsigned int anIndex)
		{
			myEmptyIndexes.push_back(anIndex);
			T* ptr = myData[anIndex * myElementSize];
			ptr->~T();
		}

		template<typename T>
		void PopBack()
		{
			assert(myNrOfElements > 0 && "Calling PopBack on empty vector");
			T* objectPointer = reinterpret_cast<T*>(&myData[myNrOfElements - 1 * myElementSize]);

			objectPointer->~T();
			myNrOfElements--;
		}

		template<typename T>
		void Grow()
		{
			myMaxNrOfElements *= static_cast<size_t>(2);
			char* oldData = myData;
			myData = new char[myMaxNrOfElements * myElementSize];
			for (size_t i = 0; i < myNrOfElements; i++)
			{
				size_t arrayIndex = i * myElementSize;

				T* oldObjectPointer = reinterpret_cast<T*>(&oldData[arrayIndex]);
				new (&myData[arrayIndex]) T(*oldObjectPointer);
				oldObjectPointer->~T();
			}
			delete[] oldData;
		}

		const size_t Size() const { return myNrOfElements - myEmptyIndexes.size(); };

		const size_t GetMaxIndex() const { return myNrOfElements; }

		template<typename T>
		T* Get(size_t anIndex)
		{
			return reinterpret_cast<T*>(&myData[anIndex * myElementSize]);
		}

		const std::vector<size_t>& GetEmptyIndexes() const
		{
			return myEmptyIndexes;
		}

	private:
		std::vector<size_t> myEmptyIndexes{};

		size_t myMaxNrOfElements = 0;
		size_t myElementSize = 0;
		size_t myNrOfElements = 0;
		char* myData = nullptr;
	};
}

namespace CU = CommonUtilities;