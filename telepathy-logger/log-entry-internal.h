/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * Copyright (C) 2009 Collabora Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Authors: Cosimo Alfarano <cosimo.alfarano@collabora.co.uk>
 */

#ifndef __TPL_LOG_ENTRY_INTERNAL_H__
#define __TPL_LOG_ENTRY_INTERNAL_H__

#include <telepathy-logger/log-entry.h>

G_BEGIN_DECLS

#define TPL_LOG_ENTRY_MSG_ID_IS_VALID(msg) (msg >= 0)

#define TPL_LOG_ENTRY_MSG_ID_UNKNOWN -2
#define TPL_LOG_ENTRY_MSG_ID_ACKNOWLEDGED -1

typedef enum
{
  TPL_LOG_ENTRY_DIRECTION_NONE = 0,

  TPL_LOG_ENTRY_DIRECTION_IN,
  TPL_LOG_ENTRY_DIRECTION_OUT
} TplLogEntryDirection;

typedef enum
{
  TPL_LOG_ENTRY_SIGNAL_NONE = 0,

  TPL_LOG_ENTRY_CHANNEL_TEXT_SIGNAL_SENT,
  TPL_LOG_ENTRY_CHANNEL_TEXT_SIGNAL_RECEIVED,
  TPL_LOG_ENTRY_CHANNEL_TEXT_SIGNAL_SEND_ERROR,
  TPL_LOG_ENTRY_CHANELL_TEXT_SIGNAL_LOST_MESSAGE,
  TPL_LOG_ENTRY_CHANNEL_TEXT_SIGNAL_CHAT_STATUS_CHANGED,

  TPL_LOG_ENTRY_CHANNEL_SIGNAL_CHANNEL_CLOSED

} TplLogEntrySignalType;

typedef enum
{
  TPL_LOG_ENTRY_ERROR,
  TPL_LOG_ENTRY_TEXT
} TplLogEntryType;


struct _TplLogEntry
{
  GObject parent;

  /* Private */
  TplLogEntryPriv *priv;
};

struct _TplLogEntryClass {
  GObjectClass parent_class;

  gint64 (*get_timestamp) (TplLogEntry *self);
  gint (*get_pending_msg_id) (TplLogEntry *self);
  gboolean (*is_pending) (TplLogEntry *self);
  TplLogEntrySignalType (*get_signal_type) (TplLogEntry *self);
  const gchar* (*get_log_id) (TplLogEntry *self);
  TplLogEntryDirection (*get_direction) (TplLogEntry *self);
  TplContact * (*get_sender) (TplLogEntry *self);
  TplContact * (*get_receiver) (TplLogEntry *self);
  const gchar * (*get_chat_id) (TplLogEntry *self);
  const gchar * (*get_account_path) (TplLogEntry *self);
  const gchar * (*get_channel_path) (TplLogEntry *self);

  void (*set_timestamp) (TplLogEntry *self, gint64 data);
  void (*set_pending_msg_id) (TplLogEntry *self, gint data);
  void (*set_signal_type) (TplLogEntry *self, TplLogEntrySignalType data);
  void (*set_log_id) (TplLogEntry *self, guint data);
  void (*set_direction) (TplLogEntry *self, TplLogEntryDirection data);
  void (*set_sender) (TplLogEntry *self, TplContact *data);
  void (*set_receiver) (TplLogEntry *self, TplContact *data);
  void (*set_chat_id) (TplLogEntry *self, const gchar *data);
  void (*set_channel_path) (TplLogEntry *self, const gchar *data);

  /* to be implemented only by subclasses */
  gboolean (*equal) (TplLogEntry *entry1, TplLogEntry *entry2);
};


void _tpl_log_entry_set_timestamp (TplLogEntry *self,
    gint64 data);

void _tpl_log_entry_set_pending_msg_id (TplLogEntry *self,
    gint data);

void _tpl_log_entry_set_signal_type (TplLogEntry *self,
    TplLogEntrySignalType data);

void _tpl_log_entry_set_direction (TplLogEntry *self,
    TplLogEntryDirection data);

void _tpl_log_entry_set_chat_id (TplLogEntry *self,
    const gchar *data);

void _tpl_log_entry_set_channel_path (TplLogEntry *self,
    const gchar *data);

void _tpl_log_entry_set_sender (TplLogEntry *self,
    TplContact *data);

void _tpl_log_entry_set_receiver (TplLogEntry *self,
    TplContact *data);

const gchar * _tpl_log_entry_get_log_id (TplLogEntry *self);

TplContact * _tpl_log_entry_get_sender (TplLogEntry *self);
TplContact * _tpl_log_entry_get_receiver (TplLogEntry *self);

gint _tpl_log_entry_get_pending_msg_id (TplLogEntry *self);
gboolean _tpl_log_entry_is_pending (TplLogEntry *self);
TplLogEntrySignalType _tpl_log_entry_get_signal_type (TplLogEntry *self);
const gchar * _tpl_log_entry_get_chat_id (TplLogEntry * self);
const gchar * _tpl_log_entry_get_channel_path (TplLogEntry *self);

TplLogEntryDirection _tpl_log_entry_get_direction (TplLogEntry *self);

gboolean _tpl_log_entry_equal (TplLogEntry *self,
    TplLogEntry *data);

G_END_DECLS
#endif // __TPL_LOG_ENTRY_INTERNAL_H__
