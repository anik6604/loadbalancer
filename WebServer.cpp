#include "WebServer.h"

/**
 * @brief Constructs a new WebServer and sets it to idle.
 */
WebServer::WebServer() : busy(false), time_remaining(0) {}

/**
 * @brief Checks if the server is currently processing a request.
 * @return true if busy, false otherwise.
 */
bool WebServer::isBusy() const {
    return busy;
}

/**
 * @brief Assigns a new request to this server.
 * @param req The request to be processed.
 */
void WebServer::assignRequest(const Request& req) {
    current_request = req;
    time_remaining = req.process_time;
    busy = true;
}

/**
 * @brief Simulates one clock cycle of processing.
 * Decreases time remaining. Frees server when done.
 */
void WebServer::processCycle() {
    if (busy) {
        --time_remaining;
        if (time_remaining <= 0) {
            busy = false;
        }
    }
}

/**
 * @brief Checks if the server has finished processing its request.
 * @return true if idle, false otherwise.
 */
bool WebServer::isDone() const {
    return !busy;
}
