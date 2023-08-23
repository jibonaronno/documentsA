void CChInfo::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_bChInfoChange = true;
	UpdateData(TRUE);
	m_bCfgChInfo = IsDlgButtonChecked(IDC_CHECK_CH_INFO_CFG);
	m_bCfgGating = IsDlgButtonChecked(IDC_CHECK_GATING_CFG);
	m_bCfgCal = IsDlgButtonChecked(IDC_CHECK_CAL_CFG);
	m_bCfgThresh = IsDlgButtonChecked(IDC_CHECK_THRESH_CFG);
	m_bCfgAmpInfo = IsDlgButtonChecked(IDC_CHECK_AMP_INFO_CFG);

	if (m_bCfgChInfo)
		GetChInfo();
	if (m_bCfgGating)
		GetGatingInfo();
	if (m_bCfgCal)
		GetCalibrationInfo();

	if (m_bCfgChInfo || m_bCfgGating || m_bCfgCal || m_bCfgThresh || m_bCfgAmpInfo)
	{
		CCuGUIDlg* pMainDlg = (CCuGUIDlg*)::AfxGetMainWnd();
		unsigned char pdd_tx_buf[55];
		CString txt;

		for (int i = 0; i < 55; i++)
			pdd_tx_buf[i] = 0;

		pdd_tx_buf[0] = 0x04;
		pdd_tx_buf[1] = 0x01;
		pdd_tx_buf[2] = 0x00;
		pdd_tx_buf[3] = 0x33;

		if (m_bCfgChInfo)
		{
			for (int i = 0; i < 24; i++)
				pMainDlg->m_nChInfo[i] = m_nChInfo[i];

			pdd_tx_buf[4] = 1;
			for (int i = 0; i < 6; i++)
				pdd_tx_buf[i + 5] = (m_nChInfo[i * 4] << 6) | (m_nChInfo[i * 4 + 1] << 5) | (m_nChInfo[i * 4 + 2] << 4) | (m_nChInfo[i * 4 + 3] << 3);
			txt.Format(L"CH Info %02x %02x %02x %02x %02x %02x", pdd_tx_buf[5], pdd_tx_buf[6], pdd_tx_buf[7], pdd_tx_buf[8], pdd_tx_buf[9], pdd_tx_buf[10]);
			if (pMainDlg->m_List.GetCount() >= 50)
				pMainDlg->m_List.ResetContent();
			pMainDlg->m_List.AddString(txt);
			pMainDlg->m_List.SetCurSel(pMainDlg->m_List.GetCount() - 1);
		}
		if (m_bCfgGating)
		{
			pdd_tx_buf[11] = 1;

			for (int i = 0; i < 24; i++)
			{
				pMainDlg->m_nGatingOnOff[i] = m_nGatingOnOff[i];
				if (m_nGatingOnOff[i])
					pdd_tx_buf[12 + i / 8] |= 0x80 >> (i % 8);
			}
			txt.Format(L"gating onoff %02x %02x %02x", pdd_tx_buf[12], pdd_tx_buf[13], pdd_tx_buf[14]);
			if (pMainDlg->m_List.GetCount() >= 50)
				pMainDlg->m_List.ResetContent();
			pMainDlg->m_List.AddString(txt);
			pMainDlg->m_List.SetCurSel(pMainDlg->m_List.GetCount() - 1);
		}

		if (m_bCfgThresh)
		{
			pdd_tx_buf[15] = 1;
			for (int i = 0; i < 6; i++)
			{
				pMainDlg->m_nGatingThres[i] = m_nGatingThres[i];
				pdd_tx_buf[16 + i * 2] = (m_nGatingThres[i] >> 8) & 0xff;
				pdd_tx_buf[17 + i * 2] = m_nGatingThres[i] & 0xff;
			}
			txt.Format(L"gating threshold %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
				pdd_tx_buf[16], pdd_tx_buf[17], pdd_tx_buf[18], pdd_tx_buf[19],
				pdd_tx_buf[20], pdd_tx_buf[21], pdd_tx_buf[22], pdd_tx_buf[23],
				pdd_tx_buf[24], pdd_tx_buf[25], pdd_tx_buf[26], pdd_tx_buf[27]);
			if (pMainDlg->m_List.GetCount() >= 50)
				pMainDlg->m_List.ResetContent();
			pMainDlg->m_List.AddString(txt);
			pMainDlg->m_List.SetCurSel(pMainDlg->m_List.GetCount() - 1);
		}

		if (m_bCfgCal)
		{
			pdd_tx_buf[28] = 1;
			for (int i = 0; i < 6; i++)
			{
				if (m_nCalInfo[i])
					pdd_tx_buf[29] |= 0x40 >> i;
			}
			txt.Format(L"Cal %02x", pdd_tx_buf[29]);
			if (pMainDlg->m_List.GetCount() >= 50)
				pMainDlg->m_List.ResetContent();
			pMainDlg->m_List.AddString(txt);
			pMainDlg->m_List.SetCurSel(pMainDlg->m_List.GetCount() - 1);
		}

		// Amp gain 설정부
		if (m_bCfgAmpInfo)
		{
			pdd_tx_buf[30] = 1;
			for (int i = 0; i < 24; i++)
			{
				int nAtt = (int)m_fAmpGain[i];
				if (nAtt < -4)
					nAtt = -4;
				if (nAtt > 27)
					nAtt = 27;
				pdd_tx_buf[31 + i] = nAtt;	// 27 - nAtt;
			}
			UpdateData(FALSE);
		}

		pMainDlg->m_Socket.Send(pdd_tx_buf, 55);
	}

	//CDialogEx::OnOK();
}
