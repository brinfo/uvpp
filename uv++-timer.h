namespace Uv
{
    class Timer: public Handle
    {
    public:
        class TimeoutHandler
        {
        private:
            virtual void OnTimeout(Timer *source, int status) = 0;

            friend class Timer;
        };

    public:
        static Timer * New(Loop &loop = Loop::Get());

        int Start(/* [in] */ TimeoutHandler &handler,
                  /* [in] */ uint64_t interval)
        {
            assert(IsOpened());

            return Start(handler, interval, interval);
        }

        int Start(/* [in] */ TimeoutHandler &handler,
                  /* [in] */ uint64_t interval,
                  /* [in] */ uint64_t delay);

        bool IsStarted()
        {
            return !! m_pHandler;
        }

        int Stop();

        Timer * Ref()
        {
            return (Timer *) Handle::Ref();
        }

    protected:
        Timer(): m_pHandler(NULL)
        {
        }

        virtual ~Timer();

        virtual int DoOpen(Loop &loop, uv_handle_t *peer);

        virtual size_t GetPeerSize() const;

        operator uv_timer_t *()
        {
            return (uv_timer_t *) GetPeer();
        }

        virtual void DoClose();

        static void OnTimeout(uv_timer_t *peer, int status);

    private:
        TimeoutHandler *m_pHandler;
    };
}
