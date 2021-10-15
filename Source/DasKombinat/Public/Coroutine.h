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
    virtual void PreTick() {}
    /**
     * Ticking.
     * Return true to make it stop ticking and be removed from the coroutine manager.
     * Returning false will make it tick again next frame.
     */
    virtual bool Tick() = 0;

    /**
     * Called automatically after the Tick() call returned true the first time.
     * After that the coroutine is discarded.
     */
    virtual void PostTick() {}
};
