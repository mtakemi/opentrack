#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#ifndef IN_OPENTRACK
/* opaque pointers, forward definitions */
struct opentrack_opaque_ctx;
typedef opentrack_opaque_ctx* opentrack;
struct opentrack_opaque_tracker;
typedef opentrack_opaque_tracker* opentrack_tracker;
#endif

#ifdef IN_OPENTRACK
#   ifdef _WIN32
#       define OPENTRACK_EXPORT __declspec(dllexport)
#   else
#       define OPENTRACK_EXPORT
#   endif
#else
#   ifdef _WIN32
#       define OPENTRACK_EXPORT __declspec(dllimport)
#   else
#       define OPENTRACK_EXPORT
#   endif
#endif

/* for `opentrack_tracker_tick', individual headpose elts */
#ifndef IN_OPENTRACK
enum opentrack_dof {
    TX = 0,
    TY,
    TZ,
    Yaw,
    Pitch,
    Roll,
    DOF_count
};
#endif

opentrack opentrack_make_ctx(const char* dir);
void opentrack_finalize_ctx(opentrack self);

/* no need to free the return value; invalid to modify it */
const char** opentrack_enum_trackers(opentrack self);

/*
 * don't `opentrack_tracker_tick an unstarted tracker, it's invalid to do so
 * it's also invalid to start a finalized tracker
 */
opentrack_tracker opentrack_make_tracker(opentrack ctx, const char* name);
void opentrack_tracker_start(opentrack self, opentrack_tracker tracker);
int opentrack_tracker_tick(opentrack_tracker tracker, double* headpose);
void opentrack_finalize_tracker(opentrack_tracker tracker);
#ifdef __cplusplus
}
#endif
