-- Sending immediately after getting IP is unreliable, so wait a second before sending --
tmr.alarm(1, 1000, 0, function()
  Transmit()
end);
