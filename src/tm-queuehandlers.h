/* Copyright (C) 2007-2010 Open Information Security Foundation
 *
 * You can copy, redistribute or modify this Program under the terms of
 * the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

/**
 * \file
 *
 * \author Victor Julien <victor@inliniac.net>
 */

#ifndef __TM_QUEUEHANDLERS_H__
#define __TM_QUEUEHANDLERS_H__

enum {
    TMQH_NOT_SET,
    TMQH_SIMPLE,
    TMQH_PACKETPOOL,
    TMQH_FLOW,

    TMQH_SIZE,
};

typedef struct Tmqh_ {
    const char *name;
    // 负责从输入队列中获取数据包或事件,并将其传递给当前线程模块进行处理。
    Packet *(*InHandler)(ThreadVars *);
    // 线程模块被关闭或停止时，确保模块能够正常地清理和释放所占用的资源。
    void (*InShutdownHandler)(ThreadVars *);
    // 将处理后的数据包或事件写入输出队列,以便将其传递给下一个线程模块或输出模块。
    void (*OutHandler)(ThreadVars *, Packet *);
    void *(*OutHandlerCtxSetup)(const char *);
    void (*OutHandlerCtxFree)(void *);
    void (*RegisterTests)(void);
} Tmqh;

extern Tmqh tmqh_table[TMQH_SIZE];

void TmqhSetup (void);
void TmqhCleanup(void);
int TmqhNameToID(const char *name);
Tmqh *TmqhGetQueueHandlerByName(const char *name);
Tmqh *TmqhGetQueueHandlerByID(const int id);

#endif /* __TM_QUEUEHANDLERS_H__ */

