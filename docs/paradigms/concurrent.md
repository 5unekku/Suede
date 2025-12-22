# Concurrent Programming

Suede provides first-class support for concurrent programming through lightweight virtual threads that are transparently multiplexed onto OS threads by the runtime scheduler.

## Virtual Threads

Virtual threads (also called green threads or user-space threads) allow spawning thousands or millions of concurrent tasks without the overhead of OS threads. The runtime automatically maps M virtual threads to N OS threads, where N typically matches CPU core count.

## The `thread<T>` Type

The `thread<T>` type represents a concurrent task that will eventually produce a value of type `T`.

Characteristics:
- Created lazily (not started immediately)
- Started explicitly with `.start()`
- Awaited to extract result
- Can be used for fire-and-forget operations

## The `async` Keyword

Use `async` to immediately start a function in a new thread without capturing a handle.

## Thread Operations

Basic operations:
- `thread<T> t = functionName` - create thread (not started)
- `t.start()` - begin execution
- `t.isRunning()` - check if still executing
- `await t` - wait and extract value (consumes thread)

Multiple thread operations:
- `await threads[]` - wait for all, return array of results
- `await.any(threads[])` - wait for first to complete

## Thread Safety

Virtual threads share memory. Proper synchronization is required for shared mutable state.

## Zero-Cost Abstraction

If `thread<T>` or `async` are not used in a program, the concurrent runtime is not linked and there is zero overhead. Concurrency is opt-in.

## Example Usage

```c++
// basic thread usage
thread<int> worker = expensiveComputation;
worker.start();
// do other work
int result = await worker;

// fire-and-forget with async
async logMessage("server started");

// awaiting multiple threads
thread<int>[] workers = { worker1, worker2, worker3 };
int[] results = await workers;
int firstResult = await.any(workers);

// independent concurrent loops
void main() {
  Game game = { 10, 10, 5, 5, true, true };
  async aiLoop(&game);
  async inputLoop(&game);
  async renderLoop(&game);
  while (game.running) {
    thread.sleep(100);
  }
}
```
