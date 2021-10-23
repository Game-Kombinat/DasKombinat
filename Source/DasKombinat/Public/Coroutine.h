#pragma once
/**
 * CoroutineManager will work on this.
 * And it will also clear the heap memory when the coroutine is done.
 */
class FCoroutine {
public:
    virtual ~FCoroutine() = default;

    /**
     * Called automatically before the first Tick() call.
     */
    virtual void PreTick() {
    }

    /**
     * Ticking.
     * Called once per frame on the main thread.
     */
    virtual void Tick() = 0;

    /**
     * Called after Tick, 
     */
    virtual bool IsDone() = 0;

    /**
     * If supported, implement logic to force an early ending
     * of the coroutine.
     */
    virtual void ForceEnd() = 0;

    /**
     * Called automatically after the coroutine notifies that it's done via IsDone()
     * After that the coroutine is discarded.
     */
    virtual void Cleanup() {
    }
};
