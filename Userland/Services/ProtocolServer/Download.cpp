/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Badge.h>
#include <ProtocolServer/ClientConnection.h>
#include <ProtocolServer/Download.h>

namespace ProtocolServer {

// FIXME: What about rollover?
static i32 s_next_id = 1;

Download::Download(ClientConnection& client, NonnullOwnPtr<OutputFileStream>&& output_stream)
    : m_client(client)
    , m_id(s_next_id++)
    , m_output_stream(move(output_stream))
{
}

Download::~Download()
{
}

void Download::stop()
{
    m_client.did_finish_download({}, *this, false);
}

void Download::set_response_headers(const HashMap<String, String, CaseInsensitiveStringTraits>& response_headers)
{
    m_response_headers = response_headers;
    m_client.did_receive_headers({}, *this);
}

void Download::set_certificate(String, String)
{
}

void Download::did_finish(bool success)
{
    m_client.did_finish_download({}, *this, success);
}

void Download::did_progress(Optional<u32> total_size, u32 downloaded_size)
{
    m_total_size = total_size;
    m_downloaded_size = downloaded_size;
    m_client.did_progress_download({}, *this);
}

void Download::did_request_certificates()
{
    m_client.did_request_certificates({}, *this);
}

}
