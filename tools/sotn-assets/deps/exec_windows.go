package deps

import (
	"os/exec"
	"syscall"
)

const DETACHED_PROCESS = 8

func cmdSetDetached(cmd *exec.Cmd) {
	cmd.SysProcAttr = &syscall.SysProcAttr{
		CreationFlags: syscall.CREATE_NEW_PROCESS_GROUP | DETACHED_PROCESS,
	}
}
