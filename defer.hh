#include <functional>

template <typename Func>
struct DeferredExecution
{
	bool cancel;
	Func fn;
	template <typename T> DeferredExecution(T &&t)
		: fn(std::forward<T>(t)), cancel(false)
	{

	}

	DeferredExecution(DeferredExecution &&other) :
		fn(std::move(other.fn)),
		cancel(other.cancel)
	{
		other.cancel = true;
	}

	DeferredExecution &operator = (DeferredExecution &&other)
	{
		if (&other != this)
		{
			fn = std::move(other.fn);
			cancel = other.cancel;
			other.cancel = true;
		}
		return *this;
	}

	void Finish()
	{
		if (cancel == false)
		{
			fn();
			Cancel();
		}
	}

	void Cancel()
	{
		cancel = true;
	}

	~DeferredExecution()
	{
		if (cancel == false) fn();
	}

private:
	DeferredExecution(const DeferredExecution &) /* = delete */;
	DeferredExecution &operator = (const DeferredExecution &) /* = delete */;
};

template<typename Func>
DeferredExecution<typename std::remove_reference<Func>::type> MakeDeferred(Func &&func)
{
	return DeferredExecution<typename std::remove_reference<Func>::type>(std::forward<Func>(func));
}
