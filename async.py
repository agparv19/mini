"""
calling a async def function does not run the function. it returns a coroutine instead.

coroutine ---> a very light weight task

asyncio.run(main()) will actually run the task/coroutine

await 

time.sleep() ----> await asyncio.sleep(delay_s)

we start all the coroutines and wait for them to finish

tasks = [asyncio.create_task(do_work(item)) for item in todo]

done, pending = await asyncio.wait(tasks)

"""
import asyncio

async def count():
    print("One")
    await asyncio.sleep(1)
    print("Two")

async def main():
    await asyncio.gather(count(), count(), count())

if __name__ == "__main__":
    import time
    s = time.perf_counter()
    asyncio.run(main())
    elapsed = time.perf_counter() - s
    print(f"{__file__} executed in {elapsed:0.2f} seconds.")