#pragma once

namespace snw
{
	class Object
	{
	public:
		Object();
		virtual ~Object();
		virtual void Destroy();

		inline bool IsPendingDestroy() const { return m_isPendingDestroy; }
	private:

		bool m_isPendingDestroy;


	};
}