// Created by eric_horacek on 4/24/20.
// Copyright © 2020 Airbnb Inc. All rights reserved.

import UIKit

// MARK: - InputAccessoryBarStackView

/// A stack of arbitrary bar views that is intended to be used as an input accessory view of a
/// keyboard.
///
/// When the keyboard is hidden, insets the bar stack's content by the bottom safe area.
///
/// Sized intrinsically, so that you don't need to call `sizeToFit` before adding it.
public final class InputAccessoryBarStackView: UIView {

  // MARK: Lifecycle

  public init(bars: [BarModeling] = []) {
    barStack = BarStackView()
    barStack.zOrder = .lastToFirst
    barStack.setBars(bars, animated: false)
    super.init(frame: .zero)
    addSubview(barStack)
    NSLayoutConstraint.activate([
      barStack.topAnchor.constraint(equalTo: topAnchor),
      barStack.leadingAnchor.constraint(equalTo: leadingAnchor),
      barStack.bottomAnchor.constraint(equalTo: bottomAnchor),
      barStack.trailingAnchor.constraint(equalTo: trailingAnchor),
    ])
    autoresizingMask = .flexibleHeight
  }

  public convenience init(@BarModelBuilder bars: () -> [BarModeling]) {
    self.init(bars: bars())
  }

  @available(*, unavailable)
  public required init?(coder _: NSCoder) {
    fatalError("init(coder:) has not been implemented")
  }

  // MARK: Public

  public let barStack: BarStackView

  public override var intrinsicContentSize: CGSize {
    barStack.systemLayoutSizeFitting(UIView.layoutFittingCompressedSize)
  }

  public override func layoutSubviews() {
    super.layoutSubviews()
    updateBarStackLayoutMarginsBottom()
  }

  public override func safeAreaInsetsDidChange() {
    super.safeAreaInsetsDidChange()
    updateBarStackLayoutMarginsBottom()
  }

  public func setBars(_ bars: [BarModeling], animated: Bool) {
    barStack.setBars(bars, animated: animated)
  }

  // MARK: Private

  private func updateBarStackLayoutMarginsBottom() {
    guard barStack.layoutMargins.bottom != safeAreaInsets.bottom else { return }

    barStack.layoutMargins.bottom = safeAreaInsets.bottom

    // Ensure that updated any layout margins are applied to the bar stack and its subviews
    // synchronously so that the invalidated intrinsic content size reflects the updated margins.
    barStack.layoutIfNeeded()

    // Resize based on the updated layout margins.
    invalidateIntrinsicContentSize()
  }

}
