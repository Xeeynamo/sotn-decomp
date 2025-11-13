//go:build !windows

package deps

import (
	"os/exec"
	"syscall"
)

func cmdSetDetached(cmd *exec.Cmd) {
	cmd.SysProcAttr = &syscall.SysProcAttr{
		Setsid: true,
	}
}
