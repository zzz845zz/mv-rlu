/**
 * @author Aleksandar Dragojevic aleksandar.dragojevic@epfl.ch
 *
 */

#ifndef WLPDSTM_DYNAMIC_EAGER_H_
#define WLPDSTM_DYNAMIC_EAGER_H_

#include <stdlib.h>

#include "../../common/word.h"
#include "../log.h"

namespace wlpdstm {

	class TransactionDynamic;

	class TxEager {

		////////////////////////////
		// public interface start //
		////////////////////////////
		public:
			// static interface
			static void TxCommitStatic(TransactionDynamic *desc);
			static void RollbackRunningStatic(TransactionDynamic *desc);
			static Word ReadWordStatic(TransactionDynamic *desc, Word *addr);
			static WriteLogEntry *LockMemoryStripeStatic(TransactionDynamic *desc, WriteLock *write_lock, Word *address);		

			// dynamic interface
			static void TxCommit(TransactionDynamic *desc);
			static void TxCommitReadOnly(TransactionDynamic *desc);
			
			static void RollbackRunning(TransactionDynamic *desc);
			
			static Word ReadWord(TransactionDynamic *desc, Word *addr);
			static Word ReadWordReadOnly(TransactionDynamic *desc, Word *addr);
#ifdef WLPDSTM_TX_PROFILING_ADAPTIVE_DYNAMIC
			static Word ReadWordProfiled(TransactionDynamic *desc, Word *addr);
			static Word ReadWordReadOnlyProfiled(TransactionDynamic *desc, Word *addr);
#endif /* WLPDSTM_TX_PROFILING_ADAPTIVE_DYNAMIC */

			static WriteLogEntry *LockMemoryStripe(TransactionDynamic *desc, WriteLock *write_lock, Word *address);
			static WriteLogEntry *LockMemoryStripeReadOnly(TransactionDynamic *desc, WriteLock *write_lock, Word *address);
#ifdef WLPDSTM_TX_PROFILING_ADAPTIVE_DYNAMIC
			static WriteLogEntry *LockMemoryStripeReadOnlyProfiled(TransactionDynamic *desc, WriteLock *write_lock, Word *address);
#endif /* WLPDSTM_TX_PROFILING_ADAPTIVE_DYNAMIC */
		
		//////////////////////////
		// public interface end //
		//////////////////////////

		protected:
			enum TryCommitResult {
				COMMIT = 0,
				JUMP_RESTART,
				RESTART_RUNNING,
				RESTART_COMMITTING
			};
			
			static TryCommitResult TxTryCommit(TransactionDynamic *desc);
			static TryCommitResult TxTryCommitReadOnly(TransactionDynamic *desc);
			static TryCommitResult TxTryCommitStatic(TransactionDynamic *desc);		
			static void TxCommitAfterTry(TransactionDynamic *desc, TryCommitResult result);

			static bool Extend(TransactionDynamic *desc);

			static void Rollback(TransactionDynamic *desc);

			static void Restart(TransactionDynamic *desc);

			static Word ReadWordInline(TransactionDynamic *desc, Word *addr);
			static Word ReadWordInnerLoop(TransactionDynamic *desc, Word *address, WriteLock *write_lock);

			static WriteLogEntry *LockMemoryStripeInline(TransactionDynamic *desc, WriteLock *write_lock, Word *address);

			static void FirstWriteSetFunPtr(TransactionDynamic *desc);
#ifdef WLPDSTM_TX_PROFILING_ADAPTIVE_DYNAMIC
			static void FirstWriteSetFunPtrProfiled(TransactionDynamic *desc);
#endif /* WLPDSTM_TX_PROFILING_ADAPTIVE_DYNAMIC */

		public:
			static void TxStartSetFunPtr(TransactionDynamic *desc);
#ifdef WLPDSTM_TX_PROFILING_ADAPTIVE_DYNAMIC
			static void TxStartSetFunPtrProfiled(TransactionDynamic *desc);
#endif /* WLPDSTM_TX_PROFILING_ADAPTIVE_DYNAMIC */
	};
}

#endif /* WLPDSTM_DYNAMIC_EAGER_H_ */
