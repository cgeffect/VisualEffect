// Created by eric_horacek on 11/3/19.
// Copyright © 2019 Airbnb Inc. All rights reserved.

import EpoxyCore
import UIKit

// MARK: - BarInstaller

/// An installer that's capable of installing a stack of fixed bars within a view controller.
final class BarInstaller<Container: BarContainer> {

  // MARK: Lifecycle

  init(viewController: UIViewController?, configuration: BarInstallerConfiguration = .shared) {
    self.viewController = viewController
    self.configuration = configuration
  }

  // MARK: Internal

  /// The container that the bars are within.
  ///
  /// Non-nil while installed, nil otherwise.
  private(set) var container: Container?

  /// Updates the bars to the given models, ordered from top to bottom.
  ///
  /// If any model corresponds to the same view as was previously set, the view will be reused and
  /// updated with the new content, optionally animated.
  ///
  /// If any model corresponds to a new bar, a new bar view will be created and inserted,
  /// optionally animated.
  ///
  /// If any model is no longer present, its corresponding view will be removed.
  func setBars(_ bars: [BarModeling], animated: Bool) {
    self.bars = bars

    guard installed, let view = viewController?.viewIfLoaded else {
      return
    }

    setBars(bars, animated: animated, in: view)
  }

  /// Installs the bar stack into the associated view controller.
  ///
  /// Should be called once the view controller loads its view. If this installer has no bar model,
  /// no view will be added. Bar views will only be added once bar models are set after installation
  /// or if bar models were set prior to installation.
  func install() {
    guard !installed else { return }

    guard let view = viewController?.viewIfLoaded else {
      EpoxyLogger.shared.assertionFailure(
        "A bar should only be installed on a view controller that's loaded its view")
      return
    }

    setBars(bars, animated: false, in: view)

    installed = true
  }

  /// Removes the bar stack from the associated view controller.
  func uninstall() {
    guard installed else { return }

    uninstallContainer()

    installed = false
  }

  // MARK: Private

  /// A stored value for an installer's coordinators.
  private struct StoredCoordinatorProperty {
    /// The current type-erased property value.
    var value: Any
    /// A closure that can be used to update a coordinator's property to the value.
    var updateCoordinator: (_ coordinator: AnyObject, _ value: Any) -> Void
  }

  private let configuration: BarInstallerConfiguration

  /// The bar models that will be set on the container once it's visible.
  private var bars: [BarModeling] = []

  /// Closures that are called whenever the bar coordinator property changes.
  private var observers = [BarCoordinatorPropertyKey: [UUID: (Any) -> Void]]()

  /// The view controller that will have its `additionalSafeAreaInsets` updated to accommodate for
  /// the bar view.
  private weak var viewController: UIViewController?

  /// Whether this installer has been installed on its view controller's view, meaning that it's
  /// safe to add a container as a subview.
  private var installed = false

  private var storage = [BarCoordinatorPropertyKey: StoredCoordinatorProperty]()

  /// Updates the models to the given collection, installing the container if needed.
  private func setBars(_ bars: [BarModeling], animated: Bool, in view: UIView) {
    self.bars = bars

    guard let container = container else {
      installContainer(in: view, with: bars, animated: animated)
      return
    }

    if let applyBars = configuration.applyBars {
      applyBars(container, bars, animated)
    } else {
      container.setBars(bars, animated: animated)
    }
  }

  private func installContainer(in view: UIView, with models: [BarModeling], animated: Bool) {
    let container = Container()
    container.didUpdateCoordinator = { [weak self] coordinator in
      self?.updateCoordinatorProperties(coordinator)
    }
    container.add(to: view)
    container.viewController = viewController
    container.setBars(models, animated: animated)
    self.container = container
  }

  private func updateCoordinatorProperties(_ coordinator: AnyBarCoordinating) {
    for value in storage.values {
      value.updateCoordinator(coordinator, value.value)
    }
  }

  private func uninstallContainer() {
    guard let container = container else { return }
    container.remove()
    self.container = nil
  }

}

// MARK: BarCoordinatorPropertyConfigurable

extension BarInstaller: BarCoordinatorPropertyConfigurable {
  public var coordinators: [AnyBarCoordinating] {
    container?.coordinators ?? []
  }

  public subscript<Property>(property: BarCoordinatorProperty<Property>) -> Property {
    get {
      (storage[property.key]?.value as? Property) ?? property.default()
    }
    set {
      storage[property.key] = .init(value: newValue, updateCoordinator: property.update)
      container?.coordinators.forEach { property.update($0, newValue) }
      observers[property.key]?.values.forEach { observer in observer(newValue) }
    }
  }

  public func observe<Property>(
    _ property: BarCoordinatorProperty<Property>,
    observer: @escaping (Property) -> Void)
    -> AnyObject
  {
    let uuid = UUID()
    // We can safely force cast as all writes to observers flow through a generic setter above
    // swiftlint:disable:next force_cast
    observers[property.key, default: [:]][uuid] = { observer($0 as! Property) }
    observer(storage[property.key]?.value as? Property ?? property.default())
    return Token { [weak self] in
      self?.observers[property.key]?[uuid] = nil
    }
  }
}

// MARK: - Token

private final class Token {

  // MARK: Lifecycle

  init(dispose: @escaping () -> Void) {
    self.dispose = dispose
  }

  deinit {
    dispose()
  }

  // MARK: Private

  private let dispose: () -> Void

}
