#include "ace/Sig_Adapter.h"

ACE_Sig_Adapter::ACE_Sig_Adapter (ACE_Sig_Action &sa, int sigkey)
  : sigkey_ (sigkey),
    type_ (SIG_ACTION),
    sa_ (sa),
    eh_ (0),
    sig_func_ (0)
{
  // ACE_TRACE ("ACE_Sig_Adapter::ACE_Sig_Adapter");
}

ACE_Sig_Adapter::ACE_Sig_Adapter (ACE_Event_Handler *eh,
                                  int sigkey)
  : sigkey_ (sigkey),
    type_ (ACE_HANDLER),
    eh_ (eh),
    sig_func_ (0)
{
  // ACE_TRACE ("ACE_Sig_Adapter::ACE_Sig_Adapter");
}

ACE_Sig_Adapter::ACE_Sig_Adapter (ACE_Sig_Handler_Ex sig_func,
                                  int sigkey)
  : sigkey_ (sigkey),
    type_ (C_FUNCTION),
    eh_ (0),
    sig_func_ (sig_func)
{
  // ACE_TRACE ("ACE_Sig_Adapter::ACE_Sig_Adapter");
}

ACE_Sig_Adapter::~ACE_Sig_Adapter ()
{
}

ACE_ALLOC_HOOK_DEFINE(ACE_Sig_Adapter)

int
ACE_Sig_Adapter::sigkey ()
{
  ACE_TRACE ("ACE_Sig_Adapter::sigkey");
  return this->sigkey_;
}

int
ACE_Sig_Adapter::handle_signal (int signum,
                                siginfo_t *siginfo,
                                ucontext_t *ucontext)
{
  ACE_TRACE ("ACE_Sig_Adapter::handle_signal");

  switch (this->type_)
    {
    case SIG_ACTION:
      {
        // We have to dispatch a handler that was registered by a
        // third-party library.

        ACE_Sig_Action old_disp;

        // Make sure this handler executes in the context it was
        // expecting...
        this->sa_.register_action (signum, &old_disp);

        ACE_Sig_Handler_Ex sig_func = ACE_Sig_Handler_Ex (this->sa_.handler ());

        (*sig_func) (signum, siginfo, ucontext);
        // Restore the original disposition.
        old_disp.register_action (signum);
        break;
      }
    case ACE_HANDLER:
      this->eh_->handle_signal (signum, siginfo, ucontext);
      break;
    case C_FUNCTION:
      (*this->sig_func_) (signum, siginfo, ucontext);
      break;
    }
  return 0;
}
