LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

TARGET_OUT = bin/android/$(TARGET_ARCH_ABI)

FLAGS = \
	-Wall \
	-Wextra \
	-Wshadow \
	-Wno-switch \
	-Wno-unused-parameter \
	-Wno-atomic-alignment \
	-std=c99 \
	-fPIC

ifdef DEBUG
FLAGS := $(FLAGS) -O0 -g
else
FLAGS := $(FLAGS) -O3 -g0 -fvisibility=hidden
endif

LOCAL_MODULE_FILENAME := libmatoya
LOCAL_MODULE := libmatoya

LOCAL_C_INCLUDES := \
	src \
	src/unix \
	src/unix/linux \
	src/unix/linux/android \
	deps

DEFS = \
	-D_POSIX_C_SOURCE=200112L \
	-DMTY_GL_ES \
	-DMTY_GL_EXTERNAL

LOCAL_CFLAGS = $(DEFS) $(FLAGS)

LOCAL_SRC_FILES := \
	src/image.c \
	src/crypto.c \
	src/file.c \
	src/json.c \
	src/log.c \
	src/memory.c \
	src/thread.c \
	src/tlocal.c \
	src/tls.c \
	src/app.c \
	src/render.c \
	src/system.c \
	src/list.c \
	src/queue.c \
	src/hash.c \
	src/version.c \
	src/hid/utils.c \
	src/gfx/gl.c \
	src/gfx/gl-ui.c \
	src/net/http.c \
	src/net/async.c \
	src/net/gzip.c \
	src/net/net.c \
	src/net/tcp.c \
	src/net/ws.c \
	src/net/secure.c \
	src/unix/system.c \
	src/unix/image.c \
	src/unix/file.c \
	src/unix/memory.c \
	src/unix/thread.c \
	src/unix/time.c \
	src/unix/net/request.c \
	src/unix/linux/dialog.c \
	src/unix/linux/android/jnih.c \
	src/unix/linux/android/crypto.c \
	src/unix/linux/android/aes-gcm.c \
	src/unix/linux/android/tls.c \
	src/unix/linux/android/gfx/gl-ctx.c \
	src/unix/linux/android/app.c \
	src/unix/linux/android/system.c \
	src/unix/linux/android/audio.c

include $(BUILD_STATIC_LIBRARY)
